# Software Requirements Specification (SRS)
## Gaming Framework — CS6015 Assignment 3

**Version:** 1.2  
**Date:** April 13, 2026  

---

## 1. Introduction

### 1.1 Purpose
This document specifies the functional and non-functional requirements for a **Gaming Framework** desktop application built with Qt/C++. The system supports user account management and a shooting game called *ShootingH*.

### 1.2 Scope
The application provides:
- User account creation, login, and guest-play modes
- Persistent player profiles with score history
- The *ShootingH* disc-shooting game with a leveling system

### 1.3 Definitions
| Term | Meaning |
|------|---------|
| User | A registered player with a saved account |
| Guest | A player without an account; scores are not saved |
| Disc | A colored game object in ShootingH worth varying points |
| Life | One of the player's 3 allowed misses before game over |
| Global Best | The highest score achieved by any registered user |
| SHA-256 | Cryptographic hash function used for password storage |

---

## 2. Overall Description

### 2.1 Product Perspective
A standalone Qt Widgets desktop application. Data is persisted in a local `users.json` file. No network connectivity is required.

### 2.2 User Classes
| Class | Description |
|-------|-------------|
| Registered User | Can sign up, sign in, play games, and view score history |
| Guest | Can play games; scores are not saved |

### 2.3 Operating Environment
- Platform: macOS (primary), Linux, Windows (Qt cross-platform)
- Compiler: C++14 or later
- Qt: 5.x (tested on 5.15.2)

---

## 3. Functional Requirements

### 3.1 User Authentication (Sprint 1)

| ID | Requirement |
|----|-------------|
| FR-01 | A user shall be able to create a new account via a sign-up form |
| FR-02 | The sign-up form shall collect: first name, last name, date of birth, gender (optional), profile picture path, username, and password |
| FR-03 | The username shall be a unique identifier; duplicate usernames shall be rejected |
| FR-04 | The password shall be at least 8 characters and contain at least one uppercase letter, one lowercase letter, and one digit |
| FR-05 | Passwords shall be stored as SHA-256 hashes; plaintext passwords shall never be persisted |
| FR-06 | A user shall be able to sign in with username and password |
| FR-07 | A user shall be able to play as a guest without an account |
| FR-08 | Upon login, the system shall display the user's name, profile picture (or initials), and the current date |
| FR-09 | If the current date matches the user's birthday, the application shall display a birthday greeting |
| FR-10 | A user shall be able to sign out and return to the login screen |

### 3.2 Score History & Profile (Sprint 1)

| ID | Requirement |
|----|-------------|
| FR-11 | A registered user shall be able to view their score history for each game |
| FR-12 | Each score entry shall show: date/time, game name, score achieved, user's personal best, and the global best score |
| FR-13 | Score history shall be sorted with the most recent entry first |
| FR-14 | Guest scores shall not be persisted |

### 3.3 ShootingH Game (Sprint 2)

| ID | Requirement |
|----|-------------|
| FR-15 | The game shall be played on a rectangular grid scene (900×560 px) |
| FR-16 | Colored discs shall spawn at the right edge and scroll left across the board |
| FR-17 | There shall be three disc types: Red (3 pts), Green (5 pts), Blue (7 pts) |
| FR-18 | The player shall shoot by clicking on a disc with the mouse |
| FR-19 | A hit disc shall turn grey and be removed after a brief flash; its point value shall be added to the score |
| FR-20 | A missed disc (exits the left edge without being hit) disappears and costs the player one life |
| FR-21 | The player starts with **3 lives**; losing all lives immediately ends the game |
| FR-22 | The HUD shall display: total score, time remaining, level, lives (❤/♡), and per-type hit counters |
| FR-23 | The game ends when either the 60-second timer expires **or** all 3 lives are lost, whichever occurs first |
| FR-24 | The game-over overlay shall state the reason for ending (`Time's up!` or `No lives left!`) |
| FR-25 | Pressing **F1** or **R** during an active game shall show a confirmation dialog (Y = restart / N or Esc = cancel) |
| FR-26 | Pressing **F1** or **R** after game over shall restart immediately without a confirmation dialog |
| FR-27 | The player shall return to the menu by pressing **Esc** after game over |
| FR-28 | The game level (1–5) shall increase every 20 points; higher levels increase disc speed and spawn rate |
| FR-29 | At level 3+, two discs shall spawn per interval |
| FR-30 | After game over, if the player is logged in, the score shall be saved automatically |

---

## 4. Non-Functional Requirements

| ID | Requirement |
|----|-------------|
| NFR-01 | All data shall be persisted in `users.json` using the JSON format |
| NFR-02 | The application shall launch in under 2 seconds on modern hardware |
| NFR-03 | The game loop shall run at approximately 33 fps (30 ms scroll tick) |
| NFR-04 | The UI shall use a consistent dark theme across all screens |
| NFR-05 | The codebase shall follow the header/source file separation convention used in class demos |
| NFR-06 | No plaintext passwords shall be stored or transmitted |

---

## 5. Data Requirements

User data (`users.json`) schema:
```json
[
  {
    "firstName": "Jane",
    "lastName": "Doe",
    "dateOfBirth": "2000-05-15",
    "gender": "Female",
    "profilePicturePath": "/path/to/pic.jpg",
    "username": "janedoe",
    "passwordHash": "<sha256-hex>",
    "scoreHistory": [
      {
        "gameName": "ShootingH",
        "score": 47,
        "timestamp": "2026-04-15T14:32:00"
      }
    ]
  }
]
```

---

## 6. Constraints
- No external libraries beyond Qt 5.x standard modules
- Must compile with `qmake` and the existing Anaconda Qt 5.15.2 environment
- No network features in scope for this assignment
