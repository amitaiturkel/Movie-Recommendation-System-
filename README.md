# Movie Recommendation System

## Overview

The Movie Recommendation System is a C++ program designed to provide movie recommendations based on user rankings and movie features. The program uses a collaborative filtering algorithm and content-based filtering to suggest movies to users.

This project consists of several classes, including `UsersLoader`, `User`, `RecommendationSystem`, `Movie`, and `RecommendationSystemLoader`, each responsible for different functionalities of the recommendation system.

## Features

- Load user data and movie rankings from a file to create users.
- Allow users to add movies to the system with their features and rankings.
- Calculate movie recommendations based on movie content and user similarity.
- Predict user ratings for a movie using collaborative filtering with the k most similar movies.

## Usage

1. Create a `RecommendationSystem` using the `RecommendationSystemLoader` and load movies from a file.
2. Load users and their movie rankings from a file using the `UsersLoader`.
3. Add movies to the `RecommendationSystem` with their features and rankings using the `User` class.
4. Calculate movie recommendations for users based on movie content and user similarity using the `RecommendationSystem` methods.

## Requirements

- C++ compiler with support for C++11 features.

## File Structure

- `users_loader.h`: Contains the `UsersLoader` class for loading users from a file.
- `user.h`: Contains the `User` class for representing users and their movie rankings.
- `recommendation_system.h`: Contains the `RecommendationSystem` class for calculating movie recommendations.
- `recommendation_system_loader.h`: Contains the `RecommendationSystemLoader` class for loading movies and creating the recommendation system.
- `movie.h`: Contains the `Movie` class for representing movies and their features.

## Note

This project is implemented as an exercise for the Intro to Computer Science course in the 2022-2023 academic year.

## Contributors

- Amitai Turkel

Feel free to contribute to this project by adding new features, improving existing code, or suggesting enhancements.

Happy Movie Recommendations!
