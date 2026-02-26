# Facebook Social Network Simulation — C++

A console-based social network simulation built in C++ that models core Facebook-like features including users, pages, posts, comments, likes, friend lists, timelines, and memory sharing.

---

## Description

This project simulates a simplified social media platform. It loads user and page data from text files, links relationships (friendships, liked pages), and supports interactive actions such as viewing timelines, liking posts, posting comments, browsing a home feed, and sharing memories. The system is built around object-oriented principles using inheritance, polymorphism, and dynamic memory management.

---

## Features

- **User & Page Management** — Load users and pages from flat files; each entity has a unique ID and display name.
- **Posts & Timelines** — Posts are associated with users or pages and displayed chronologically on their timelines.
- **Likes & Comments** — Users can like posts and add comments; all interactions are tied to a current logged-in user.
- **Home Feed** — Aggregates recent posts (within 3 days) from the user's friends and liked pages.
- **Memories** — On-this-day feature surfaces old posts from the same calendar date in prior years, which can then be reshared.
- **Sorting** — Timelines for both users and pages are sorted in reverse chronological order.
- **Date System** — A static `Date::Today` drives all relative time display (e.g., "1H", "2D", or full date).

---

## Project Structure

```
.
├── main.cpp                        # All source code (single-file project)
├── Users.txt                       # User data (ID, first name, last name)
├── Pages.txt                       # Page data (ID, title)
├── Posts.txt                       # Post data (ID, date, text, shared by, liked by)
├── comments.txt                    # Comment data (ID, post ID, user ID, text)
└── FriendListAndLikedPages.txt     # Friendship and page-like relationships
```

---

## Class Overview

| Class | Role |
|---|---|
| `helper` | Static utility functions (string ops, ID generation) |
| `Date` | Stores day/month/year; holds a static `Today` instance |
| `Object` | Abstract base for `User` and `Page`; owns a post timeline |
| `Post` | A post with text, date, likes, and comments |
| `Memory` | Extends `Post`; wraps an original post as a memory reshare |
| `Comment` | A comment linked to a post and its author |
| `User` | A social user with friends, liked pages, and a timeline |
| `Page` | A page with a title and its own timeline |
| `Controller` | Orchestrates data loading, user session, and all commands |

---

## Input File Formats

### `Users.txt`
```
<total_users>
<user_id> <first_name> <last_name>
...
```

### `Pages.txt`
```
<total_pages>
<page_id>\t<page_title>
...
```

### `Posts.txt`
```
<total_posts>
<post_id> <day> <month> <year>
<post_text>
<shared_by_id> <liked_by_id1> <liked_by_id2> ... -1
...
```

### `comments.txt`
```
<total_comments>
<comment_id> <post_id> <commenter_id>
<comment_text>
...
```

### `FriendListAndLikedPages.txt`
```
<user_id> <friend_id1> <friend_id2> ... -1 <page_id1> <page_id2> ... -1
...
-1
```

---

## How to Build & Run

### Requirements
- A C++11 (or later) compatible compiler (e.g., `g++`, MSVC)

### Compile
```bash
g++ -std=c++11 -o facebook main.cpp
```

### Run
```bash
./facebook
```

Make sure all five `.txt` data files are in the same directory as the executable.

---

## Demo Sequence (hardcoded in `Controller::Run()`)

The `Run()` method executes a fixed demo walkthrough:

1. Sets the current date to **17/4/2024**
2. Sets the current user to **u7**
3. Displays u7's friend list and liked pages
4. Displays u7's timeline
5. Views who liked **post5**, then likes it as u7
6. Views the timeline of **page p1**
7. Views u7's home feed
8. Posts comments on **post4** and **post8**
9. Views the updated home feed
10. Runs the **See Memories** feature for u7
11. **Shares a memory** of post10 with custom text
12. Sorts and displays u7's final timeline

To switch to interactive mode, uncomment the `cin` lines inside `Run()`.

---

## Known Limitations

- Fixed array sizes (max 10 friends, 10 liked pages, 10 likes, 10 comments per post)
- No persistent write-back to files after runtime changes
- No input validation beyond basic ID matching
- Single-file architecture — all classes reside in `main.cpp`

---

## Author

Built as an academic OOP project in C++ demonstrating class hierarchies, polymorphism, file I/O, and manual memory management.
