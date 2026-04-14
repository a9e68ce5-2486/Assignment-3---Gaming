# Work Distribution — Gaming Framework

## Team Members

| Member | Role |
|--------|------|
| Sheng-Hung Tseng | Data layer, home/profile UI, game timer & level logic |
| Min-Shan Lee | Auth logic, login/signup UI, game scene core, navigation |

---

## Sprint 1 Distribution

| Component | File(s) | Owner |
|-----------|---------|-------|
| Data model | `user.h`, `user.cpp` | Sheng-Hung Tseng |
| JSON persistence | `userdatabase.h`, `userdatabase.cpp` | Sheng-Hung Tseng |
| Auth business logic | `authmanager.h`, `authmanager.cpp` | Min-Shan Lee |
| Login screen | `loginscreen.h`, `loginscreen.cpp` | Min-Shan Lee |
| Sign-up screen | `signupscreen.h`, `signupscreen.cpp` | Min-Shan Lee |
| Home screen | `homescreen.h`, `homescreen.cpp` | Sheng-Hung Tseng |
| Profile screen | `profilescreen.h`, `profilescreen.cpp` | Sheng-Hung Tseng |
| UI styling | `styles.h` | Sheng-Hung Tseng |
| SRS document | `docs/SRS.md` | Both |
| UML diagram | `docs/UML.md` | Min-Shan Lee |
| Sprint backlog | `docs/sprint_backlog.md` | Both |
| Work distribution | `docs/work_distribution.md` | Both |

---

## Sprint 2 Distribution

| Component | File(s) | Owner |
|-----------|---------|-------|
| Disc game object | `disc.h`, `disc.cpp` | Sheng-Hung Tseng |
| Game scene (HUD, overlay) | `gamescene.h`, `gamescene.cpp` | Min-Shan Lee |
| Spawn / scroll timers | (inside `gamescene.cpp`) | Min-Shan Lee |
| Mouse shooting + hit logic | (inside `gamescene.cpp`) | Min-Shan Lee |
| 60-second game timer | (inside `gamescene.cpp`) | Sheng-Hung Tseng |
| Level-up system | (inside `gamescene.cpp`) | Sheng-Hung Tseng |
| Game-score save to profile | (inside `mainwindow.cpp`) | Sheng-Hung Tseng |
| Main window + navigation | `mainwindow.h`, `mainwindow.cpp` | Min-Shan Lee |
| Project file | `gaming_framework.pro` | Min-Shan Lee |
| Integration & end-to-end testing | All | Both |

---

## Responsibility Matrix (RACI)

| Task | Sheng-Hung Tseng | Min-Shan Lee |
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
