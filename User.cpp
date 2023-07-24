

// don't change those includes
#include <algorithm>
#include "User.h"
#include "RecommendationSystem.h"


User::User(const std::string& username, rank_map& ratings,
           std::shared_ptr<RecommendationSystem> &rs){
  Username = username;
  ranks = ratings;
  recommendationSystem = rs;
}

const std::string& User::get_name() const{
  return Username;
}
void User::add_movie_to_rs(const std::string &name, int year,
                           const std::vector<double> &features,
                           double rate) {


  // Add the movie to the RecommendationSystem
  sp_movie movie = recommendationSystem->add_movie(name,year, features);
  // Add the movie and its rating to the ranks map
  ranks[movie] = rate;
}
const std::unordered_map<sp_movie, double, hash_func, equal_func> &
User::get_ranks () const
{
  return ranks;
}
sp_movie User::get_recommendation_by_content() const{
  return recommendationSystem->recommend_by_content (*this);
}
sp_movie User::get_recommendation_by_cf(int k) const{
  return recommendationSystem->recommend_by_cf (*this,k);
}
double User::get_prediction_score_for_movie (const std::string &name, int year, int k) const
{
  return recommendationSystem->predict_movie_score
      (*this, recommendationSystem->get_movie (name, year), k);
}

std::ostream& operator<<(std::ostream& os, const User& user) {
  os << "name: " << user.get_name() << std::endl;
  os<< *user.recommendationSystem << std::endl;
  return os;
}







