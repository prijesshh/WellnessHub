#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include<limits>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
using namespace std;

string todayString()
{
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", now);
    return string(buf);
}

void toLowerStr(string& s)
{
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
}

float lastValue(const string& fname)
{
    ifstream f(fname);
    if (!f) return 0.0f;
    string last, line;
    while (getline(f, line)) last = line;
    return last.empty() ? 0.0f : stof(last);
}

void green(const string& s) { cout << "\033[32m" << s << "\033[0m"; }
void red(const string& s)   { cout << "\033[31m" << s << "\033[0m"; }

class pin
{
private:
    string initialpin;
    string newpin;
    int attempts = 3;

public:
    pin()
    {
        initialpin = "open";
    }

    void check()
    {
        while (attempts > 0)
        {
            string t;
            cout << "Enter 'open' to continue: ";
            cin >> t;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            toLowerStr(t);                         
            if (t == initialpin && attempts != 0)
            {
                cout << "Access granted" << endl;
                break;
            }
            else if (attempts == 0)
            {
                cout << "Too many incorrect attempts \n Access denied.......";
                exit(0);
            }
            attempts--;
            cout << attempts << " Attempts are left" << endl;
        }
    }

    void authentication()
    {
        attempts = 3;
        string extract;
        ifstream file("pin.txt");
        if (file.is_open())
        {
            getline(file, extract);
            file.close();
        }
        if (extract.empty())
        {
            initialpin = "open";
        }
        else
        {
            initialpin = extract;
        }
        while (attempts > 0)
        {
            string temp;
            cout << "Enter your 'old' password: ";
            cin >> temp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            toLowerStr(temp);                           
            if (temp == initialpin && attempts != 0)
            {
                cout << "Enter your 'new' password: ";
                cin >> newpin;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                ofstream file("pin.txt");
                if (file.is_open())
                {
                    file << newpin << endl;
                    file.close();
                    cout << "Password changed and saved successfully\n";
                }
                else
                {
                    cout << "Failed to save password \n";
                }

                newcheck();
                break;
            }

            else if (attempts == 0)
            {
                cout << "Too many incorrect attempts \n Access denied.......";
                exit(0);
            }
            attempts--;
            cout << attempts << " Attempts are left" << endl;
        }
    }

    void newcheck()
    {
        attempts = 3;
        string temp;
        string checkpin;
        ifstream file("pin.txt");

        if (file.is_open())
        {
            getline(file, checkpin);
            file.close();
        }
        else
        {
            cout << "Unknown error occured\n";
        }
        while (attempts > 0)
        {
            cout << "Enter your password: ";
            cin >> temp;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            toLowerStr(temp);                          
            if (checkpin == temp && attempts != 0)
            {
                cout << "Access granted" << endl;
                break;
            }
            else if (attempts == 0)
            {
                cout << "To many incorrect attempts \n Access denied....";
                exit(0);
            }
            attempts--;
            cout << attempts << " Attempts are left" << endl;
        }
    }
};

class person
{
protected:
    string name;
    int age;
    float height;

public:
    void inputpersondata()
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter your name:" << endl;
        getline(cin, name);          

        cout << "Enter your age:" << endl;
        cin  >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  

        cout << "Enter your height in cm:" << endl;
        cin  >> height;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  

        set_in_file();   
    }

    void set_in_file()
    {
        ofstream file("person.txt");
        if (file.is_open())
        {
            file << name << endl;
            file << age << endl;
            file << height << endl;
            file.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }
    }
};

class HealthData : public person
{
protected:
    float water_intake;
    float weight;
    float sleep;
    int BP_systolic;
    int BP_diastolic;
    int steps;
    float BMI;
    float calories;
    float BMR;

public:
    void inputdata()
    {
        string temp;
        ifstream file("person.txt");
        if (file.is_open())
        {
            getline(file, temp);
            file.close();
        }
        if (temp.empty())
        {
            inputpersondata();
        }

        ifstream filep("person.txt");
        if (filep.is_open())
        {
            getline(filep, name);
            string agetemp, heighttemp;
            getline(filep, agetemp);
            getline(filep, heighttemp);
            age = stoi(agetemp);
            height = stof(heighttemp);
            filep.close();
        }
        else
        {
            cout << "Failed to open person file after writing." << endl;
            return;
        }

        float prevWater = lastValue("water.txt");
        float prevSleep = lastValue("sleep.txt");
        float prevSteps = lastValue("steps.txt");

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "enter your water intake in litres:" << endl;
        cout << " (prev " << prevWater << ") : ";
        string wline; 
        getline(cin, wline);
        if (wline.empty()) water_intake = prevWater;
        else water_intake = stof(wline);

        cout << "enter your weight in kg:" << endl;
        cin >> weight;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "enter your sleep in hours:" << endl;
        cout << " (prev " << prevSleep << ") : ";
        string sline;
        getline(cin, sline);
        if (sline.empty()) sleep = prevSleep;
        else sleep = stof(sline);

        cout << "enter your BP_systolic:" << endl;
        cin >> BP_systolic;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "enter your BP_diastolic:" << endl;
        cin >> BP_diastolic;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "enter your steps:" << endl;
        cout << " (prev " << static_cast<int>(prevSteps) << ") : ";
        string stline; 
        getline(cin, stline);
        if (stline.empty()) steps = static_cast<int>(prevSteps);
        else steps = stoi(stline);

        calculations();
    }

    void calculations()
    {
        BMI = weight / ((height / 100) * (height / 100));
        BMR = 10 * weight + 6.25 * height - 5 * age + 5;
        calories = BMR * 1.2;
        set_to_file();
    }

    void loadPersonal()
    {
        ifstream f("person.txt");
        if (!f) return;
        getline(f, name);
        string a, h;
        getline(f, a);
        getline(f, h);
        age    = a.empty() ? 0 : stoi(a);
        height = h.empty() ? 0.0f : stof(h);
    }

    void loadLastSaved()
    {
        ifstream w("water.txt");
        if (w) {
            string lastW;
            while (getline(w, lastW)) {}
            if (!lastW.empty()) water_intake = stof(lastW);
            w.close();
        }

        ifstream s("sleep.txt");
        if (s) {
            string lastS;
            while (getline(s, lastS)) {}
            if (!lastS.empty()) sleep = stof(lastS);
            s.close();
        }

        ifstream wt("weight.txt");
        if (wt) {
            string lastWt;
            while (getline(wt, lastWt)) {}
            if (!lastWt.empty()) weight = stof(lastWt);
            wt.close();
        }

        ifstream st("steps.txt");
        if (st) {
            string lastSt;
            while (getline(st, lastSt)) {}
            if (!lastSt.empty()) steps = stoi(lastSt);
            st.close();
        }

        ifstream b("BMI.txt");
        if (b) {
            string lastB;
            while (getline(b, lastB)) {}
            if (!lastB.empty()) BMI = stof(lastB);
            b.close();
        }

        ifstream bp("BP.txt");
        if (bp) {
            string lastBP;
            while (getline(bp, lastBP)) {}
            if (!lastBP.empty())
                sscanf(lastBP.c_str(), "%d/%d", &BP_systolic, &BP_diastolic);
            bp.close();
        }

        ifstream c("calories.txt");
        if (c) {
            string lastC;
            while (getline(c, lastC)) {}
            if (!lastC.empty()) calories = stof(lastC);
            c.close();
        }

        BMR = 10 * weight + 6.25 * height - 5 * age + 5;
    }

    void showdata()
    {
        if (name.empty())
        {
            loadPersonal();
        }

        if (water_intake == 0.0f && sleep == 0.0f)
        {
            loadLastSaved();
        }

        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Water Intake: " << water_intake << " litres" << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Sleep: " << sleep << " hours" << endl;
        cout << "Blood Pressure: " << BP_systolic << "/" << BP_diastolic << endl;
        cout << "Steps: " << steps << endl;
        cout << "BMI: " << BMI << endl;
        cout << "BMR (Assuming minimal activity): " << BMR << " kcal/day" << endl;
        cout << "Approximate calories Burned: " << calories << endl;
    }

    void set_to_file()
    {
        ofstream file("water.txt", ios::app);
        if (file.is_open())
        {
            file << water_intake << endl;
            file.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }

        ofstream file1("weight.txt", ios::app);
        if (file1.is_open())
        {
            file1 << weight << endl;
            file1.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }

        ofstream file2("sleep.txt", ios::app);
        if (file2.is_open())
        {
            file2 << sleep << endl;
            file2.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }

        ofstream file3("BP.txt", ios::app);
        if (file3.is_open())
        {
            file3 << BP_systolic << "/" << BP_diastolic << endl;
            file3.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }

        ofstream file4("BMI.txt", ios::app);
        if (file4.is_open())
        {
            file4 << BMI << endl;
            file4.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }

        ofstream file5("calories.txt", ios::app);
        if (file5.is_open())
        {
            file5 << calories << endl;
            file5.close();
        }
        else
        {
            cout << "Failed to open file for writing." << endl;
        }
    }

    void history()
    {
        cout << "...Displaying history..." << endl;
        ifstream file("water.txt");
        if (file.is_open())
        {
            string line;
            cout << "Water Intake History:" << endl;
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Failed to open water intake history file." << endl;
        }

        ifstream file1("weight.txt");
        if (file1.is_open())
        {
            string line;
            cout << "Weight History:" << endl;
            while (getline(file1, line))
            {
                cout << line << endl;
            }
            file1.close();
        }
        else
        {
            cout << "Failed to open weight history file." << endl;
        }

        ifstream file2("sleep.txt");
        if (file2.is_open())
        {
            string line;
            cout << "Sleep History:" << endl;
            while (getline(file2, line))
            {
                cout << line << endl;
            }
            file2.close();
        }
        else
        {
            cout << "Failed to open sleep history file." << endl;
        }

        ifstream file3("BP.txt");
        if (file3.is_open())
        {
            string line;
            cout << "Blood Pressure History:" << endl;
            while (getline(file3, line))
            {
                cout << line << endl;
            }
            file3.close();
        }
        else
        {
            cout << "Failed to open blood pressure history file." << endl;
        }

        ifstream file4("BMI.txt");
        if (file4.is_open())
        {
            string line;
            cout << "BMI History:" << endl;
            while (getline(file4, line))
            {
                cout << line << endl;
            }
            file4.close();
        }
        else
        {
            cout << "Failed to open BMI history file." << endl;
        }

        ifstream file5("calories.txt");
        if (file5.is_open())
        {
            string line;
            cout << "Calories Burned History:" << endl;
            while (getline(file5, line))
            {
                cout << line << endl;
            }
            file5.close();
        }
        else
        {
            cout << "Failed to open calories burned history file." << endl;
        }
    }
};

class PeriodCycle
{
private:
    string startDate;
    string endDate;
    int flowLevel;

public:
    void logPeriod()
    {
        cout << "Enter period start date (YYYY-MM-DD or 't' for today): ";
        cin >> startDate;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (startDate == "t" || startDate == "T") startDate = todayString(); 
        cout << "Enter period end date   (YYYY-MM-DD or 't' for today): ";
        cin >> endDate;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (endDate == "t" || endDate == "T") endDate = todayString();     
        cout << "Flow level (1=light, 2=medium, 3=heavy): ";
        cin >> flowLevel;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ofstream file("period_cycle.txt", ios::app);
        if (file.is_open())
        {
            file << startDate << " " << endDate << " " << flowLevel << endl;
            file.close();
            cout << "Period cycle logged." << endl;
        }
        else
        {
            cout << "Failed to open period file." << endl;
        }
    }

    void viewLastCycles()
    {
        ifstream file("period_cycle.txt");
        if (!file.is_open())
        {
            cout << "No period data yet." << endl;
            return;
        }
        vector<string> allLines;
        string line;
        while (getline(file, line)) allLines.push_back(line);
        file.close();

        int count = 0;
        cout << "--- Last Cycles (max 3) ---" << endl;
        for (int i = allLines.size() - 1; i >= 0 && count < 3; --i, ++count)
        {
            stringstream ss(allLines[i]);
            string s, e;
            int f;
            ss >> s >> e >> f;
            cout << "Start: " << s << "  End: " << e << "  Flow: " << f << endl;
        }
        if (count == 0) cout << "No cycles recorded." << endl;
    }
};

class Goal:public person
{
protected:
    float waterGoal;
    float sleepGoal;
    float weightGoal;

public:
    float readHeight() const
    {
        ifstream f("person.txt");
        if (!f) return 170.0f;
        string n, a, h;
        getline(f, n);
        getline(f, a);
        getline(f, h);
        return h.empty() ? 170.0f : stof(h);
    }

    float computeGoalWeight() const
    {
        float hCM = readHeight();
        float hM  = hCM / 100.0f;
        return 22.0f * hM * hM;
    }

    Goal()
    {
        waterGoal = 3;
        sleepGoal = 8;
        weightGoal = computeGoalWeight();;
    }

    void initializeGoalFile()
    {
        ifstream file("goal.txt");
        if (!file.is_open())
        {
            ofstream newfile("goal.txt");
            if (newfile.is_open())
            {
                newfile<<fixed<<setprecision(1);
                newfile << waterGoal << " " << sleepGoal << " " << weightGoal << endl;
                newfile.close();
            }
        }
        else
        {
            file.close();
        }
    }

    void loadGoalFromFile()
    {
        ifstream file("goal.txt");
        if (file.is_open())
        {
            file >> waterGoal >> sleepGoal >> weightGoal;
            file.close();
        }
    }

    void showGoal()
    {
        loadGoalFromFile();
        cout << "-----Current Goals-----" << endl;
        cout << "Water Intake: " << waterGoal << " L" << endl;
        cout << "Sleep: " << sleepGoal << " hr" << endl;
        cout << "Weight: " << weightGoal << " kg" << endl;
    }

    void changeGoal()
    {
        cout << "Enter new water intake goal: " << "l";
        cin >> waterGoal;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter new sleep goal: " << "hr";
        cin >> sleepGoal;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Enter new weight goal: " << "kg";
        cin >> weightGoal;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        ofstream file("goal.txt");
        if (file.is_open())
        {
            file << waterGoal << " " << sleepGoal << " " << weightGoal << endl;
            file.close();
            cout << "Goals updated successfully!" << endl;
        }
    }

    void showGoalsForBar() const
    {
        cout << "Water " << waterGoal << " L  " << "Sleep " << sleepGoal << " h  " << "Weight " << weightGoal << " kg";
    }

    float getWaterGoal() const { return waterGoal; }
    float getSleepGoal() const { return sleepGoal; }
    float getWeightGoal() const { return weightGoal; }
};

class Quote
{
private:
    string quoteOfDay;

public:
    void setQuote()
    {
        string quotes[10] =
        {
            "Push yourself, because no one else is going to do it for you.",
            "Success doesn't just find you. You have to go out and get it.",
            "Great things never come from comfort zones.",
            "Dream it. Wish it. Do it.",
            "Don't stop when you're tired. Stop when you're done.",
            "Work hard in silence, let success make the noise.",
            "The key to success is to focus on goals, not obstacles.",
            "Discipline is the bridge between goals and accomplishment.",
            "Start where you are. Use what you have. Do what you can.",
            "The harder you work for something, the greater you'll feel when you achieve it."
        };

        srand(static_cast<unsigned>(time(nullptr)));
        int index = rand() % 10;
        quoteOfDay = quotes[index];
    }

    void displayQuote()
    {
        cout << "\n------ Quote of the Day ------" << endl;
        cout << quoteOfDay << "\n\n";
    }
};

void clearAllDataFiles()
{
    const char* files[] =
    {
        "water.txt",
        "weight.txt",
        "sleep.txt",
        "BP.txt",
        "BMI.txt",
        "calories.txt",
        "steps.txt",
        "person.txt",
        "pin.txt",
        "goal.txt",
        "period_cycle.txt"
    };
    int n = sizeof(files) / sizeof(files[0]);

    for (int i = 0; i < n; i++)
    {
        ofstream file(files[i], ios::trunc);
        if (file.is_open())
        {
            file.close();
        }
        else
        {
            cout << "Failed to clear " << files[i] << endl;
        }
    }
    cout << "All data files cleared successfully!" << endl;
}

void summaryBar()
{
    float w = lastValue("water.txt");
    float s = lastValue("sleep.txt");
    float st= lastValue("steps.txt");

    Goal g;
    g.loadGoalFromFile();

    cout << "\n----- Today vs Goal -----\n";

    if (w >= g.getWaterGoal()) green("Water ");
    else red("Water ");
    cout << fixed << setprecision(1) << w << "/" << g.getWaterGoal() << " L  ";

    if (s >= g.getSleepGoal()) green("Sleep ");
    else red("Sleep ");
    cout << s << "/" << g.getSleepGoal() << " h  ";

    float curWt = lastValue("weight.txt");
    if (curWt > 0) {
        if (curWt <= (g.getWeightGoal()+5) && curWt >= (g.getWeightGoal()-5)) green("Weight ");
        else red("Weight ");
        cout << curWt << "/" << g.getWeightGoal() << " kg";
    }

    cout << endl;
}

void periodHint()
{
    ifstream f("period_cycle.txt");
    if (!f) return;
    vector<string> all;
    string line;
    while (getline(f, line)) all.push_back(line);
    f.close();
    if (all.empty()) return;
    stringstream ss(all.back());
    string lastS, lastE;
    int fl;
    ss >> lastS >> lastE >> fl;
    int y, m, d;
    sscanf(lastS.c_str(), "%d-%d-%d", &y, &m, &d);
    tm t = {};
    t.tm_year = y - 1900;
    t.tm_mon  = m - 1;
    t.tm_mday = d;
    time_t raw = mktime(&t) + 28 * 86400;
    tm* next   = localtime(&raw);
    char nxt[11];
    strftime(nxt, sizeof(nxt), "%Y-%m-%d", next);
    cout << "Next period estimated: " << nxt << " (approx)" << endl;
}

void quickLog()
{
    float prevW = lastValue("water.txt");
    float prevS = lastValue("sleep.txt");
    float prevSt = lastValue("steps.txt");

    cout << "--- Quick Log (skip=Enter) --- " << endl;

    string wline;
    cout << "Water (L) (prev " << prevW << "): ";
    getline(cin, wline);
    float water = wline.empty() ? prevW : stof(wline);

    string sline;
    cout << "Sleep (h) (prev " << prevS << "): ";
    getline(cin, sline);
    float sleep = sline.empty() ? prevS : stof(sline);

    string stline;
    cout << "Steps (prev " << static_cast<int>(prevSt) << "): ";
    getline(cin, stline);
    int steps = stline.empty() ? static_cast<int>(prevSt) : stoi(stline);

    ofstream("water.txt", ios::app) << water << '\n';
    ofstream("sleep.txt", ios::app) << sleep << '\n';
    ofstream("steps.txt", ios::app) << steps << '\n';
    
    cout << "Quick log saved.\n";
}

int main()
{
    pin pass;
    HealthData data_per;
    Goal goal;
    Quote quote;
    PeriodCycle period;

    string extract;
    ifstream file("pin.txt");
    if (file.is_open())
    {
        getline(file, extract);
        file.close();
    }

    if (extract.empty())
    {
        pass.check();
    }
    else
    {
        pass.newcheck();
    }

    goal.initializeGoalFile();
    goal.loadGoalFromFile();
    quote.setQuote();

    cout << "\nWelcome back!\n";
    periodHint();
    summaryBar();

    int choice;
    do
    {
        quote.displayQuote();

        cout << "\t1.Data" << endl;
        cout << "\t2.Display history" << endl;
        cout << "\t3.Personal goals" << endl;
        cout << "\t4.Period cycle" << endl;
        cout << "\t5.Change password" << endl;
        cout << "\t6.Clear all stored data" << endl;
        cout << "\t7.Exit" << endl;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            int achoice;
            cout << "\t1.Enter data" << endl;
            cout << "\t2.Show data" << endl;
            cout << "\t0.Quick log (water/sleep/steps only)" << endl;   
            cin >> achoice;
            switch (achoice)
            {
            case 0:                                    
                quickLog();
                break;
            case 1:
                data_per.inputdata();
                break;
            case 2:
                data_per.showdata();
                break;
            default:
                cout << "incorrect option" << endl;
                break;
            }
            break;
        }
        case 2:
            data_per.history();
            break;
        case 3:
        {
            int gchoice;
            cout << "\t1.Show goal" << endl;
            cout << "\t2.Change goal" << endl;
            cin >> gchoice;
            switch (gchoice)
            {
            case 1:
                goal.showGoal();
                break;
            case 2:
                goal.changeGoal();
                break;
            default:
                cout << "incorrect option" << endl;
                break;
            }
            break;
        }
        case 4:
        {
            int pchoice;
            cout << "\t1.Log period" << endl;
            cout << "\t2.View last cycles" << endl;
            cin >> pchoice;
            switch (pchoice)
            {
            case 1:
                period.logPeriod();
                break;
            case 2:
                period.viewLastCycles();
                break;
            default:
                cout << "incorrect option" << endl;
                break;
            }
            break;
        }
        case 5:
            pass.authentication();
            break;
        case 6:
        {
            cout << "Are you sure you want to clear all stored data? (y/n): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                clearAllDataFiles();
            }
            else
            {
                cout << "Clear data cancelled." << endl;
            }
            break;
        }
        case 7:
            cout << "exiting the program.......";
            exit(0);
        default:
            cout << "incorrect option" << endl;
            break;
        }
    } while (choice != 7);

    return 0;
}