# Recommendation System

The "Recommendation System" project consists of a C++ implementation that provides functionalities to recommend movies to users based on their preferences and movie features. It includes several classes to facilitate the process of movie recommendations.

## Table of Contents

- [Introduction](#introduction)
- [Movie Class](#movie-class)
- [RecommendationSystem Class](#recommendationsystem-class)
- [RecommendationSystemLoader Class](#recommendationsystemloader-class)
- [User Class](#user-class)
- [UsersLoader Class](#usersloader-class)

## Introduction

The "Recommendation System" project is designed to help users discover new movies based on their preferences and the movie features. It leverages various algorithms and techniques to make personalized movie recommendations.

## Movie Class

The `Movie` class represents a movie with its name and the year it was made. It includes functionalities to compare movies based on their year and name. The class also supports output stream operator overloading to display movie information.

## RecommendationSystem Class

The `RecommendationSystem` class manages movies in the system and offers recommendation functionalities. It includes features to add new movies, calculate movie scores based on features and user rankings, and recommend movies to users by content or collaborative filtering.

## RecommendationSystemLoader Class

The `RecommendationSystemLoader` class is responsible for loading movies and their features into the RecommendationSystem from a file in a specified format.

## User Class

The `User` class represents a user in the recommendation system and includes functionalities to add movies to the system, get movie recommendations based on content or collaborative filtering, and predict movie scores for a given user.

## UsersLoader Class

The `UsersLoader` class is responsible for loading users and their movie rankings from a file and creating user objects for the recommendation system.

Feel free to use this README.md as a template for your project. Just make sure to update the content with any specific details or modifications relevant to your project.
