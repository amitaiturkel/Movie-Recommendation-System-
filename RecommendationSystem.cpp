#include "RecommendationSystem.h"
#include "cmath"

bool compared_descending(double a, double b)
{
  return a > b;
}
double calculate_cosine_similarity(const std::vector<double>& vec1, const std::vector<double>& vec2)
{
  // Check if the input vectors have the same size
  if (vec1.size() != vec2.size())
  {
    throw std::invalid_argument("Input vectors must have the same size");
  }

  double dot_product = 0.0;
  double norm_vec1 = 0.0;
  double norm_vec2 = 0.0;

  for (size_t i = 0; i < vec1.size(); i++)
  {
    dot_product += vec1[i] * vec2[i];
    norm_vec1 += vec1[i] * vec1[i];
    norm_vec2 += vec2[i] * vec2[i];
  }

  // Handle edge case when one or both vectors are zero vectors
  if (norm_vec1 == 0.0 || norm_vec2 == 0.0)
  {
    throw std::invalid_argument("Input vectors must not be zero vectors");
  }

  double similarity = dot_product / (std::sqrt(norm_vec1) * std::sqrt
      (norm_vec2));

  return similarity;
}

sp_movie RecommendationSystem::recommend_by_content(const User& user)
{
  auto rank = user.get_ranks ();
  // TODO check deep copy
  double rank_sum = 0;
  int rank_size = 0;

  // Step 1: Calculate the average rank of the user's ratings
  for (const auto &pair: rank)
  {
    rank_size++;
    rank_sum += pair.second;
  }//check
  double average_rank = rank_sum / rank_size;

  // Subtract the average rank from the user's ratings to normalize them
  for (auto &pair: rank)
  {
    pair.second -= average_rank;
  }

  // Step 2: Create the feature preference vector
  std::vector<double> feature_preferences(sortedmap.begin()->second.size(),
                                          0.0);
  for (const auto &movie_rank_user: rank)
  {
    const sp_movie &movie = movie_rank_user.first;
    const double user_rank = movie_rank_user.second;
    const std::vector<double> &movie_features = sortedmap[movie];
    for (long unsigned int i = 0; i < movie_features.size(); i++)
    {
      feature_preferences[i] += user_rank * movie_features[i];
    }
  }
  sp_movie recommended_movie;
  double max_similarity = -1.0;
  for(auto movie_and_features : sortedmap){
    if(rank.find (movie_and_features.first) == rank.end() ) {
      // movie isn"t there
      double similarity = calculate_cosine_similarity(feature_preferences,
                                                      movie_and_features.second);

      if (similarity > max_similarity)
      {
        max_similarity = similarity;
        recommended_movie = movie_and_features.first;
      }
    }
  }

  return recommended_movie;
}

sp_movie RecommendationSystem::recommend_by_cf(const User& user, int k) {
  auto rank = user.get_ranks();
  sp_movie recommended_movie;
  double max_predicted_rating = -30.0;

  for (auto movie_and_features : sortedmap) {
    if (rank.find(movie_and_features.first) == rank.end()) {
      // Movie hasn't been rated by the user
      std::map<sp_movie, double> similarity_to_movie;
      std::map<double, sp_movie, decltype(compared_descending)*> to_find_n
      (compared_descending);
      for (auto movie_that_user_saw : sortedmap) {
        if (rank.find(movie_that_user_saw.first) != rank.end()) {
          // Movie has been rated by the user
          sp_movie movie_user_saw = movie_that_user_saw.first;
          const std::vector<double>& movie_user_saw_feature = movie_that_user_saw.second;
          double  calc = calculate_cosine_similarity(movie_user_saw_feature, movie_and_features.second);
          similarity_to_movie[movie_user_saw] = calc;
          to_find_n.emplace (calc,movie_user_saw);
        }
      }

      // Find the top k movies with the highest similarity
      std::vector<sp_movie> n_movies;
      auto it = to_find_n.begin();
      for (int i = 0; i < k; ++i) {
        n_movies.push_back(it->second);
        ++it;
      }

      // Calculate the sum of similarity scores and the sum of ranks for the similar movies
      double sum_of_similarity = 0.0;
      double sum_of_rank = 0.0;
      for (const auto& similar_movie : n_movies) {
        sum_of_rank += similarity_to_movie[similar_movie] *
                       rank[similar_movie];
        sum_of_similarity += similarity_to_movie[similar_movie];
      }

      // Calculate the predicted rating for the movie
      double predicted_rating = sum_of_rank / sum_of_similarity;

      if (predicted_rating > max_predicted_rating) {
        max_predicted_rating = predicted_rating;
        recommended_movie = movie_and_features.first;
      }
    }
  }

  return recommended_movie;
}





sp_movie RecommendationSystem::get_movie(const std::string& name, int year)
const {
  for (const auto& movie_pair : sortedmap) {
    const sp_movie& movie = movie_pair.first;
    if (movie->get_name() == name && movie->get_year() == year) {
      return movie;
    }
  }
  return nullptr;
}
sp_movie RecommendationSystem::add_movie(const std::string& name, int year, const std::vector<double>& features) {
  auto movie = std::make_shared<Movie>(name, year);
  sortedmap.emplace(movie, features);


  return movie;
}

double RecommendationSystem::predict_movie_score(const User& user_rankings, const sp_movie& movie, int k) {
    auto rank = user_rankings.get_ranks();
    std::map<sp_movie, double> similarity_to_movie;
  std::map<double, sp_movie, decltype(compared_descending)*> find_k(compared_descending);


  for (auto movie_that_user_saw : rank) {
      sp_movie movie_user_saw = movie_that_user_saw.first;
      const std::vector<double>& movie_user_saw_feature = sortedmap[movie_user_saw];
      double calc = calculate_cosine_similarity(movie_user_saw_feature, sortedmap[movie]);
      similarity_to_movie[movie_user_saw] = calc;
      find_k[calc] = movie_user_saw;
    }
    // Find the top k movies with the highest similarity
    std::vector<sp_movie> n_movies;
    auto find_k_it = find_k.begin();
    for (int i = 0; i < k; ++i) {
      n_movies.push_back(find_k_it->second);
      ++find_k_it;
    }

    // Calculate the sum of similarity scores and the sum of ranks for the similar movies
    double sum_of_similarity = 0.0;
    double sum_of_rank = 0.0;
    for (const auto& similar_movie : n_movies) {
      sum_of_rank += similarity_to_movie[similar_movie] *
          rank[similar_movie];
      sum_of_similarity += similarity_to_movie[similar_movie];
    }

    // Calculate the predicted rating for the movie
    double predicted_rating = sum_of_rank / sum_of_similarity;

    return predicted_rating;
  }
std::ostream& operator<<(std::ostream& os,  RecommendationSystem const& rs)
{
  for (const auto& pair : rs.sortedmap)
  {
    const sp_movie& movie = pair.first;
    os << *movie << '\n';
  }

  return os;
}

