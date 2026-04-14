# Project & Sprint Backlog — Gaming Framework

## Sprint Timeline

| Sprint | Dates | Focus |
|--------|-------|-------|
| Sprint 1 | April 12 – April 16 | Planning + User Auth + Profiles |
| Sprint 2 | April 17 – April 21 | ShootingH Game + Integration + Polish |

---

## Product Backlog (Full)

| ID  | User Story | Priority | Sprint | Status |
|-----|-----------|----------|--------|--------|
| PB-01 | As a user, I can sign up with my personal info | High | 1 | Done |
| PB-02 | As a user, I can sign in with username & password | High | 1 | Done |
| PB-03 | As a visitor, I can play as a guest | High | 1 | Done |
| PB-04 | Password is validated (8+ chars, upper, lower, digit) | High | 1 | Done |
| PB-05 | Username is unique | High | 1 | Done |
| PB-06 | Profile picture displayed on home screen | Medium | 1 | Done |
| PB-07 | Current date shown on home screen | Medium | 1 | Done |
| PB-08 | Birthday greeting shown on login day | Medium | 1 | Done |
| PB-09 | View score history with personal best & global best | High | 1 | Done |
| PB-10 | Disc-shooting game (ShootingH) playable | High | 2 | Done |
| PB-11 | Three disc types: Red (3pt), Green (5pt), Blue (7pt) | High | 2 | Done |
| PB-12 | HUD shows score, time, level, per-type counters | High | 2 | Done |
| PB-13 | 60-second game timer | High | 2 | Done |
| PB-14 | Level system (1–5) speeds up discs | Medium | 2 | Done |
| PB-15 | Score auto-saved for logged-in users | High | 2 | Done |
| PB-16 | Press R/F1 to start; Esc to return after game over | Medium | 2 | Done |
| PB-17 | Floating score popup on hit | Low (bonus) | 2 | Done |
| PB-18 | Disc grey-flash before removal | Low (bonus) | 2 | Done |
| PB-19 | Grid background in game scene | Low (bonus) | 2 | Done |
| PB-20 | Dark theme UI across all screens | Low (bonus) | 1 | Done |
| PB-21 | 3-lives system — miss a disc costs one life | High | 2 | Done |
| PB-22 | Lives displayed as ❤/♡ in HUD; time turns red at ≤10s | Medium | 2 | Done |
| PB-23 | Game ends when lives = 0 or time = 0 (first to occur) | High | 2 | Done |
| PB-24 | Game-over overlay shows end reason + lives remaining | Medium | 2 | Done |
| PB-25 | Restart confirmation dialog during active game (Y/N) | Medium | 2 | Done |

---

## Sprint 1 Backlog (April 12–16)

### Goals
- Planning documents (SRS, UML, Sprint Backlog, Work Distribution)
- User data model and JSON persistence
- Authentication: sign up, sign in, guest
- Home screen with profile display + birthday greeting
- Profile screen with score history table

### Tasks

| Task | Owner | Est. Hours | Status |
|------|-------|-----------|--------|
| Write SRS | Team | 2h | Done |
| Draw UML class diagram | Team | 2h | Done |
| Define sprint backlog | Team | 1h | Done |
| Implement `User` + `ScoreEntry` (model) | Dev A | 2h | Done |
| Implement `UserDatabase` (JSON I/O) | Dev A | 2h | Done |
| Implement `AuthManager` (sign up/in/out) | Dev B | 2h | Done |
| Implement `LoginScreen` UI | Dev B | 2h | Done |
| Implement `SignUpScreen` UI | Dev B | 3h | Done |
| Implement `HomeScreen` UI | Dev A | 2h | Done |
| Implement `ProfileScreen` UI | Dev A | 2h | Done |
| Implement `MainWindow` (navigation) | Dev B | 2h | Done |
| Styling (`styles.h` dark theme) | Dev A | 1h | Done |
| Integration & testing Sprint 1 | Both | 2h | Done |

**Sprint 1 Velocity: ~27 story points**

---

## Sprint 2 Backlog (April 17–21)

### Goals
- ShootingH game (scene, discs, HUD, timers, levels)
- 3-lives system with dual end conditions
- Restart confirmation dialog
- Game-score save integration
- Polish, testing, final packaging

### Tasks

| Task | Owner | Est. Hours | Status |
|------|-------|-----------|--------|
| Implement `Disc` class (type, points, markHit) | Dev A | 2h | Done |
| Implement `GameScene` HUD setup | Dev B | 2h | Done |
| Implement spawn timer + disc scrolling | Dev B | 3h | Done |
| Implement mouse-click shooting | Dev B | 2h | Done |
| Implement 60-second game timer + end game | Dev A | 2h | Done |
| Implement level system (speed/spawn rate) | Dev A | 1h | Done |
| Implement game-over overlay | Dev B | 1h | Done |
| Implement floating score popups | Dev A | 1h | Done |
| Implement 3-lives system (miss = -1 life) | Dev A | 1h | Done |
| Implement dual end condition (time or lives = 0) | Dev A | 1h | Done |
| Lives HUD (❤/♡) + time warning color | Dev A | 1h | Done |
| Implement restart confirmation dialog (Y/N) | Dev B | 1h | Done |
| Connect game score to user profile | Dev B | 1h | Done |
| End-to-end testing (auth → game → history) | Both | 3h | Done |
| Final bug fixes and polish | Both | 2h | Done |

**Sprint 2 Velocity: ~25 story points**

---

## Definition of Done
- Feature compiles without warnings
- Feature behaves correctly in manual testing
- Score data persists correctly to `users.json`
- UI matches dark theme style guide

---

## Repository

🔗 **https://github.com/a9e68ce5-2486/Assignment-3---Gaming**
