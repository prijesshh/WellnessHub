# 🏥 WellnessHub

**Your Personal Health Command Center** ⚡

> *Born from a semester project and a personal mission to kick inactivity to the curb!*

## 🎯 What's This About?

WellnessHub is a terminal-based health tracking system that helps you monitor daily wellness metrics and smash your health goals. Whether you're trying to drink more water, get better sleep, walk more steps, or track your menstrual cycle—this tool has your back.

**The Origin Story**: Started as my second semester project, but evolved into something more personal when I realized I was spending way too much time sitting and not enough time moving. So I built a system to hold myself accountable. Now you can use it too! 💪

## ✨ Features

### 📊 What You Can Track
- 💧 **Water Intake** - Stay hydrated, friends!
- 😴 **Sleep Hours** - Because rest matters
- 🚶 **Steps Count** - Get those 10,000 steps (or whatever works for you)
- 🌸 **Period Cycles** - Comprehensive menstrual cycle logging

### 🎨 Smart Features
- ✅ **Color-Coded Goal Summary** - Instant visual feedback (Green = crushing it, Red = needs work)
- 🎯 **Auto Weight Goal Calculation** - Based on your height
- 📈 **Previous Values Display** - See your last entries for context
- 🔒 **Secure Access** - PIN/password protection (case-insensitive for convenience)
- 📝 **Last 3 Period Cycles** - Quick reference to recent cycles
- 📊 **Daily Summary Bar** - Compare today's metrics vs. your goals at a glance
- 💾 **Persistent Storage** - Your data is saved across sessions

### 🛠️ Technical Goodness
- Modern C++ with STL (vectors, stringstream, algorithms)
- Robust input handling with `getline` and `cin.ignore`
- Reusable helper functions for clean, maintainable code
- File-based data persistence (`water.txt`, `sleep.txt`, `steps.txt`, `period_cycle.txt`)
- Case-insensitive authentication for better UX

## 🚀 Getting Started

### Prerequisites
- C++ compiler (g++, clang++, or MSVC)
- Terminal/Command Prompt
- A desire to be healthier!

### Installation

```bash
# Clone the repository
git clone https://github.com/PurnikaKhanal/project.git
cd project/Update

# Compile the program
g++ -std=c++11 -o wellnesshub main.cpp

# Run it!
./wellnesshub
```

### First Time Setup
1. Launch the program
2. Create your account with a PIN/password
3. Set your health goals
4. Start tracking!

## 💡 How to Use

```
🏥 Welcome to WellnessHub!

1. Log Water Intake
2. Log Sleep Hours
3. Log Steps
4. Log Period Cycle
5. View Today's Summary
6. View Goal Progress
7. View Last 3 Period Cycles
8. Update Goals
9. Exit
```

**Pro Tips:**
- Log your data daily for best results
- The system shows your previous values when entering new data
- Green summaries = you're on track! Red = time to step it up!
- Your data persists, so you can close and reopen anytime

## 🎯 Coming Soon

### 🚀 Planned Upgrades
- **GUI/UX Makeover** - Moving from terminal to a beautiful graphical interface
- **Hardware Integration** - Automatic tracking with smart sensors:
  - Fitness tracker integration for steps
  - Smart water bottle connectivity
  - Sleep monitoring via wearables
- **Data Visualization** - Beautiful charts and graphs of your progress
- **Mobile App** - Track on the go
- **Export Reports** - Generate weekly/monthly health reports

### 💭 Ideas for Improvement

**Want to contribute? Here are some areas that could use love:**

#### 🎨 User Experience
- Add data visualization (line graphs showing trends over time)
- Weekly/monthly summary reports
- Achievement system and streak tracking
- Reminder notifications for logging data
- Dark mode for terminal interface

#### 🔧 Technical Enhancements
- Database integration (SQLite) instead of text files
- Data export to CSV/JSON
- Multi-user support with profiles
- Cloud sync capabilities
- API for third-party app integration

#### 📊 Feature Extensions
- Calorie tracking and meal logging
- Exercise/workout logging
- Mood tracking
- Medication reminders
- Custom metric creation
- Goal recommendations based on health data
- Integration with popular fitness apps (Fitbit, Apple Health, Google Fit)

#### 🔐 Security & Privacy
- Encrypted data storage
- Backup and restore functionality
- Data privacy controls

#### 🌟 Advanced Features
- AI-powered health insights and recommendations
- Predictive analytics for period cycles
- Social features (compare progress with friends, challenges)
- Voice input for hands-free logging
- Smart goal adjustment based on progress

## 🏗️ Project Structure

```
Update/
├── main.cpp              # Main program logic
├── water.txt            # Water intake data
├── sleep.txt            # Sleep hours data
├── steps.txt            # Steps count data
├── period_cycle.txt     # Period cycle data
├── goals.txt            # Your health goals
└── README.md            # You are here!
```

## 🤝 Contributing

Found a bug? Have a cool feature idea? Contributions are welcome!

1. Fork the repo
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 Notes

- This is a terminal-based application (for now!)
- Data is stored locally in text files
- All measurements use standard units (liters for water, hours for sleep, steps for activity)
- The program is designed for personal use and single-user tracking

## 🎓 Academic Context

This project started as an extension of my second semester Computer Engineering coursework. What began as a class assignment became a personal tool for tracking my own health journey, and hopefully yours too!

## 📄 License

This project is open source and available for anyone looking to improve their health tracking game!

## 💪 Motivation

*"The journey of a thousand miles begins with a single step... and tracking that step in WellnessHub."*

Built with 💙 by someone who realized sitting all day wasn't cutting it.

---

**Stay healthy, stay coding!** 🚀💻🏃‍♀️
