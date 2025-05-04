# Vibesta
## Vibes that stay, Moments that slay 
## Overview
Vibesta is a social networking platform developed in C++ that allows users to sign up, log in, send friend requests, view friends, suggest new friends, and share and display their interests. It uses a combination of linked lists, hashing, and graph-based data structures to manage user information, interests, and friendships. The project also includes a "famous interest" feature for which it uses max heap that displays the most popular interests across the platform with the number of users who have that interest tagged.

## Features
### User Authentication:
Users can sign up with a username and password.

Users can log in with their credentials.

Authentication checks prevent duplicate user creation.

### Interests Management:
Users can add, view, and display their interests.

Interests are stored using a linked list data structure for each user.

A "famous interest" feature shows the most popular interest across all users.

### Friendship Management:
Users can send friend requests to others.

The platform allows users to view their friends.

It supports mutual friends and friend suggestions based on shared interests and mutual connections.

### Graph Representation of Friendships:
Users and their friendships are represented using graphs.

Friendships are dynamic, and the graph is updated when new connections are made.

### Friend Suggestions:
The platform suggests new friends based on mutual interests and mutual friends.

## Data Structures Used
Linked Lists: Used for storing user interests and friendships.

Hash Tables: Used for managing user interests efficiently.

Graphs: Represent users and their friendships.

Max Heap: To rank interest by popularity.

## Setup and Installation
### 1.Clone the repository:
    git clone https://github.com/your-username/Vibesta.git
### 2.Navigate to the project directory:
    cd Vibesta
### 3.Build the project (using any C++ compatible compiler like g++):
    g++ main.cpp -o vibesta
### 4.Run the program:
    ./vibesta
## File Structure
  /Vibesta
  
  |-- main.cpp            # Entry point of the program

  |-- Interests.txt       # File to store user interests

  |-- User.txt            # File to store user login credentials

  |-- graph.txt           # File to store the friendship graph

  |-- README.md           # Project documentation

## Usage
### Sign Up: 
  When running the application, you can choose to sign up by entering a username and password.

### Log In:
  After signing up, users can log in to access their account.

### Main Menu: 
Once logged in, users can:
#### Add and view interests.

#### Send friend requests.

#### View friends and mutual friends.

#### Get friend suggestions based on mutual interests.

#### See the most popular interest across all users.

## Important Notes
The application currently reads from and writes to local files (User.txt, Interests.txt, and graph.txt), which store user credentials, interests, and friendship data.

The project uses a simplistic text-based menu to interact with the user.
