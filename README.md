# Gaming Framework — CS6015 Assignment 3

A Qt/C++ desktop gaming framework with user account management and the **ShootingH** disc-shooting game.

---

## Features

### User System
- Sign up (first name, last name, DOB, gender, profile picture, username, password)
- Sign in / Play as Guest
- Password validation: 8+ characters, uppercase, lowercase, digit
- SHA-256 password hashing
- Birthday greeting on login day
- Persistent storage via `users.json`

### Profile & Score History
- View score history per game
- Personal best vs. global best comparison
- Scores auto-saved for registered users

### ShootingH Game
- 3 disc types: 🔴 Red (3 pts) · 🟢 Green (5 pts) · 🔵 Blue (7 pts)
- 3 lives — miss a disc and lose one life
- 60-second timer — first of time or lives to zero ends the game
- Level system 1–5: speed and spawn rate increase every 20 points
- HUD: score, time (turns red at ≤10s), level, lives (❤/♡), per-type counters
- Floating score popups on hit, `-1 ❤` popup on miss
- Restart confirmation dialog during active game (Y = restart / N = keep playing)

---

## Build Instructions

### Requirements
- Qt 5.x (tested on Qt 5.15.2)
- C++14 compiler (clang / g++)
- qmake

### Steps
```bash
qmake gaming_framework.pro
make -j4
./gaming_framework.app/Contents/MacOS/gaming_framework   # macOS
# or
./gaming_framework                                        # Linux
```

---

## Project Structure

```
Assignment3/
├── docs/
│   ├── SRS.md                 # Software Requirements Specification
│   ├── UML.md                 # Class diagram & navigation flow
│   ├── sprint_backlog.md      # Product & sprint backlogs
│   └── work_distribution.md  # Team roles & RACI matrix
├── main.cpp
├── styles.h                   # Shared dark-theme stylesheet
├── user.h / user.cpp          # User model + ScoreEntry + SHA-256 hashing
├── userdatabase.h / .cpp      # JSON persistence singleton
├── authmanager.h / .cpp       # Auth business logic singleton
├── loginscreen.h / .cpp       # Login UI
├── signupscreen.h / .cpp      # Sign-up form UI
├── homescreen.h / .cpp        # Home screen (profile + birthday greeting)
├── profilescreen.h / .cpp     # Score history table
├── mainwindow.h / .cpp        # QStackedWidget navigation hub
├── disc.h / disc.cpp          # Game disc (Red / Green / Blue)
├── gamescene.h / gamescene.cpp# ShootingH game scene
└── gaming_framework.pro       # qmake project file
```

---

## Game Controls

| Key | Action |
|-----|--------|
| Mouse click | Shoot a disc |
| F1 or R | Start / Restart (confirmation dialog during game) |
| Y | Confirm restart |
| N or Esc | Cancel restart / Return to menu after game over |

---

## Sprint Timeline

| Sprint | Dates | Deliverables |
|--------|-------|-------------|
| Sprint 1 | Apr 12–16 | Planning docs, user auth, profiles |
| Sprint 2 | Apr 17–21 | ShootingH game, lives system, polish |

---

## Team
> Add team member names here.

---

*Built with Qt 5.15.2 · C++14 · CS6015 Spring 2026*
