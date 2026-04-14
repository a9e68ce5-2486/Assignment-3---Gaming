# UML Class Diagram — Gaming Framework

## Class Relationships Overview

```
                    ┌──────────────────────┐
                    │      MainWindow       │  (QMainWindow)
                    │──────────────────────│
                    │ - m_stack            │
                    │ - m_loginScreen      │◄──── owns
                    │ - m_signUpScreen     │◄──── owns
                    │ - m_homeScreen       │◄──── owns
                    │ - m_profileScreen    │◄──── owns
                    │ - m_gameScene        │◄──── owns
                    │ - m_gameView         │◄──── owns
                    │──────────────────────│
                    │ + showLogin()        │
                    │ + showSignUp()       │
                    │ + showHome()         │
                    │ + showProfile()      │
                    │ + showGame()         │
                    │ + onGameOver(score)  │
                    └──────────────────────┘
                            │ uses
              ┌─────────────┼───────────────┐
              ▼             ▼               ▼
   ┌──────────────┐  ┌────────────┐  ┌──────────────┐
   │ AuthManager  │  │UserDatabase│  │  GameScene   │
   │ (singleton)  │  │ (singleton)│  │              │
   └──────────────┘  └────────────┘  └──────────────┘
```

---

## Detailed Class Definitions

### Data Layer

```
┌─────────────────────────────────────────┐
│               ScoreEntry                │
├─────────────────────────────────────────┤
│ + gameName   : QString                  │
│ + score      : int                      │
│ + timestamp  : QDateTime                │
├─────────────────────────────────────────┤
│ + toJson()   : QJsonObject              │
│ + fromJson() : ScoreEntry  [static]     │
└─────────────────────────────────────────┘
                    ◄─── aggregated by User (0..*)

┌─────────────────────────────────────────┐
│                  User                   │
├─────────────────────────────────────────┤
│ + firstName          : QString          │
│ + lastName           : QString          │
│ + dateOfBirth        : QDate            │
│ + gender             : QString          │
│ + profilePicturePath : QString          │
│ + username           : QString          │
│ + passwordHash       : QString          │
│ + scoreHistory       : QVector<ScoreEntry>│
├─────────────────────────────────────────┤
│ + isBirthdayToday()  : bool             │
│ + addScore(game,n)   : void             │
│ + bestScore(game)    : int              │
│ + toJson()           : QJsonObject      │
│ + fromJson(obj)      : User  [static]   │
│ + hashPassword(pw)   : QString [static] │
│ + checkPassword(pw,h): bool   [static]  │
└─────────────────────────────────────────┘

┌─────────────────────────────────────────┐
│           UserDatabase  «singleton»     │
├─────────────────────────────────────────┤
│ - m_users    : QVector<User>            │
│ - m_filePath : QString                  │
├─────────────────────────────────────────┤
│ + instance()          : UserDatabase&  [static]│
│ + load(path)          : bool            │
│ + save()              : bool            │
│ + addUser(user)       : bool            │
│ + findUser(username)  : User*           │
│ + updateUser(user)    : bool            │
│ + usernameExists(u)   : bool            │
│ + globalBestScore(g)  : int             │
└─────────────────────────────────────────┘
```

### Business Logic Layer

```
┌─────────────────────────────────────────┐
│          AuthManager  «singleton»       │   ◄── QObject
├─────────────────────────────────────────┤
│ - m_currentUser : User*                 │
│ - m_isGuest     : bool                  │
├─────────────────────────────────────────┤
│ + instance()           : AuthManager&  [static]│
│ + signUp(user, err)    : bool           │
│ + signIn(u,pw, err)    : User*          │
│ + signOut()            : void           │
│ + playAsGuest()        : void           │
│ + currentUser()        : User*          │
│ + isGuest()            : bool           │
│ + validatePassword(pw) : bool  [static] │
│ + validateUsername(u)  : bool  [static] │
├─────────────────────────────────────────┤
│ «signal» userLoggedIn(User*)            │
│ «signal» userLoggedOut()               │
└─────────────────────────────────────────┘
         │ uses
         ▼
   UserDatabase
```

### Game Layer

```
┌─────────────────────────────────────────┐
│           Disc  ◄── QObject             │
│                 ◄── QGraphicsEllipseItem│
├─────────────────────────────────────────┤
│ - m_type   : DiscType  {Red,Green,Blue} │
│ - m_points : int                        │
│ - m_hit    : bool                       │
├─────────────────────────────────────────┤
│ + discType() : DiscType                 │
│ + points()   : int                      │
│ + isHit()    : bool                     │
│ + markHit()  : void                     │
└─────────────────────────────────────────┘
           ◄─── managed by GameScene (0..*)

┌─────────────────────────────────────────────────────────┐
│               GameScene  ◄── QGraphicsScene             │
├─────────────────────────────────────────────────────────┤
│ - m_spawnTimer  : QTimer*                               │
│ - m_scrollTimer : QTimer*                               │
│ - m_gameTimer   : QTimer*                               │
│ - m_hudBg             : QGraphicsRectItem*              │
│ - m_scoreText         : QGraphicsTextItem*              │
│ - m_timeText          : QGraphicsTextItem*              │
│ - m_levelText         : QGraphicsTextItem*              │
│ - m_livesText         : QGraphicsTextItem*              │
│ - m_redText           : QGraphicsTextItem*              │
│ - m_greenText         : QGraphicsTextItem*              │
│ - m_blueText          : QGraphicsTextItem*              │
│ - m_overlayBg         : QGraphicsRectItem*              │
│ - m_overlayText       : QGraphicsTextItem*              │
│ - m_confirmBg         : QGraphicsRectItem*              │
│ - m_confirmText       : QGraphicsTextItem*              │
│ - m_confirmingRestart : bool                            │
│ - m_score             : int                             │
│ - m_redHits           : int                             │
│ - m_greenHits         : int                             │
│ - m_blueHits          : int                             │
│ - m_timeLeft          : int                             │
│ - m_level             : int    (1–5)                    │
│ - m_lives             : int    (0–3)                    │
│ - m_running           : bool                            │
│ - SCENE_W             : int = 900  [const]              │
│ - SCENE_H             : int = 560  [const]              │
│ - HUD_H               : int = 60   [const]              │
│ - GAME_DURATION       : int = 60   [const]              │
│ - MAX_LIVES           : int = 3    [const]              │
├─────────────────────────────────────────────────────────┤
│ + startGame()             : void                        │
│ + restartGame()           : void                        │
│ + finalScore()            : int                         │
│ + finalLevel()            : int                         │
│ «slot» spawnDisc()        : void                        │
│ «slot» scrollDiscs()      : void                        │
│ «slot» tickTimer()        : void                        │
├─────────────────────────────────────────────────────────┤
│ «signal» gameOver(score: int)                           │
│ «signal» returnToMenu()                                 │
├─────────────────────────────────────────────────────────┤
│ # mousePressEvent(event)  : void  [override]            │
│ # keyPressEvent(event)    : void  [override]            │
│ # drawBackground(p, rect) : void  [override]            │
└─────────────────────────────────────────────────────────┘
```

### UI Layer

```
┌─────────────────────────────────────────┐
│          LoginScreen  ◄── QWidget       │
├─────────────────────────────────────────┤
│ - m_usernameEdit : QLineEdit*           │
│ - m_passwordEdit : QLineEdit*           │
│ - m_errorLabel   : QLabel*             │
├─────────────────────────────────────────┤
│ + clearFields()       : void            │
│ + showError(msg)      : void            │
│ «signal» signInClicked(u, pw)           │
│ «signal» signUpClicked()               │
│ «signal» guestClicked()                │
└─────────────────────────────────────────┘

┌─────────────────────────────────────────┐
│         SignUpScreen  ◄── QWidget       │
├─────────────────────────────────────────┤
│ - m_firstNameEdit        : QLineEdit*   │
│ - m_lastNameEdit         : QLineEdit*   │
│ - m_dobEdit              : QDateEdit*   │
│ - m_genderCombo          : QComboBox*   │
│ - m_profilePicEdit       : QLineEdit*   │
│ - m_usernameEdit         : QLineEdit*   │
│ - m_passwordEdit         : QLineEdit*   │
│ - m_confirmPasswordEdit  : QLineEdit*   │
│ - m_errorLabel           : QLabel*     │
├─────────────────────────────────────────┤
│ + clearFields()  : void                 │
│ + showError(msg) : void                 │
│ «signal» signUpSubmitted(...)           │
│ «signal» backClicked()                 │
└─────────────────────────────────────────┘

┌─────────────────────────────────────────┐
│          HomeScreen  ◄── QWidget        │
├─────────────────────────────────────────┤
│ - m_avatarLabel   : QLabel*            │
│ - m_nameLabel     : QLabel*            │
│ - m_dateLabel     : QLabel*            │
│ - m_greetingLabel : QLabel*            │
├─────────────────────────────────────────┤
│ + refresh() : void                      │
│ «signal» playGameClicked()             │
│ «signal» profileClicked()              │
│ «signal» signOutClicked()              │
└─────────────────────────────────────────┘

┌─────────────────────────────────────────┐
│        ProfileScreen  ◄── QWidget       │
├─────────────────────────────────────────┤
│ - m_avatarLabel : QLabel*              │
│ - m_infoLabel   : QLabel*              │
│ - m_scoreTable  : QTableWidget*        │
├─────────────────────────────────────────┤
│ + refresh() : void                      │
│ «signal» backClicked()                 │
└─────────────────────────────────────────┘
```

---

## Navigation Flow

```
  App Start
      │
      ▼
 ┌──────────┐  sign up  ┌────────────┐
 │  Login   │──────────►│  Sign Up  │
 │  Screen  │◄──────────│  Screen   │
 └──────────┘   back    └────────────┘
      │
      │ sign in / guest
      ▼
 ┌──────────┐  play     ┌────────────┐
 │  Home    │──────────►│   Game    │
 │  Screen  │◄──────────│  (Esc)    │
 └──────────┘  Esc/done └────────────┘
      │
      │ profile
      ▼
 ┌──────────┐
 │ Profile  │
 │  Screen  │──► back ──► Home
 └──────────┘
```

---

## Key Design Patterns Used

| Pattern | Where Applied |
|---------|---------------|
| Singleton | `AuthManager`, `UserDatabase` — single source of truth for state/data |
| Observer (Qt signals/slots) | All screen-to-MainWindow navigation; GameScene events |
| Facade | `MainWindow` coordinates all screens and auth logic |
| Value Object | `ScoreEntry`, `User` — serializable data containers |
