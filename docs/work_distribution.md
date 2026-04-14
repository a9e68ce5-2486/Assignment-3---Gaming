# Work Distribution — Gaming Framework

## Team Members

| Member | Role |
|--------|------|
| Dev A | Data layer, home/profile UI, game timer & level logic |
| Dev B | Auth logic, login/signup UI, game scene core, navigation |

> Replace "Dev A / Dev B" with actual team member names before submission.

---

## Sprint 1 Distribution

| Component | File(s) | Owner |
|-----------|---------|-------|
| Data model | `user.h`, `user.cpp` | Dev A |
| JSON persistence | `userdatabase.h`, `userdatabase.cpp` | Dev A |
| Auth business logic | `authmanager.h`, `authmanager.cpp` | Dev B |
| Login screen | `loginscreen.h`, `loginscreen.cpp` | Dev B |
| Sign-up screen | `signupscreen.h`, `signupscreen.cpp` | Dev B |
| Home screen | `homescreen.h`, `homescreen.cpp` | Dev A |
| Profile screen | `profilescreen.h`, `profilescreen.cpp` | Dev A |
| UI styling | `styles.h` | Dev A |
| SRS document | `docs/SRS.md` | Both |
| UML diagram | `docs/UML.md` | Dev B |
| Sprint backlog | `docs/sprint_backlog.md` | Both |
| Work distribution | `docs/work_distribution.md` | Both |

---

## Sprint 2 Distribution

| Component | File(s) | Owner |
|-----------|---------|-------|
| Disc game object | `disc.h`, `disc.cpp` | Dev A |
| Game scene (HUD, overlay) | `gamescene.h`, `gamescene.cpp` | Dev B |
| Spawn / scroll timers | (inside `gamescene.cpp`) | Dev B |
| Mouse shooting + hit logic | (inside `gamescene.cpp`) | Dev B |
| 60-second game timer | (inside `gamescene.cpp`) | Dev A |
| Level-up system | (inside `gamescene.cpp`) | Dev A |
| Game-score save to profile | (inside `mainwindow.cpp`) | Dev A |
| Main window + navigation | `mainwindow.h`, `mainwindow.cpp` | Dev B |
| Project file | `gaming_framework.pro` | Dev B |
| Integration & end-to-end testing | All | Both |

---

## Responsibility Matrix (RACI)

| Task | Dev A | Dev B |
|------|-------|-------|
| Requirements gathering | R | R |
| Architecture / class design | C | R |
| Data layer implementation | R | I |
| Auth logic implementation | I | R |
| UI screens implementation | R | R |
| Game implementation | R | R |
| Integration | R | R |
| Testing | R | R |
| Documentation | R | R |

**R** = Responsible, **C** = Consulted, **I** = Informed

---

## Git Workflow
- `main` branch: stable, always buildable
- Feature branches: `feature/auth`, `feature/game`, etc.
- Merge to `main` via pull request after peer review
- Commit messages follow: `[Sprint N] short description`

---

## Repository

🔗 **https://github.com/a9e68ce5-2486/Assignment-3---Gaming**
