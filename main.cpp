#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

// 定義學生資料結構
struct Student {
    string id;
    string name;
    int score;
};

// ---------------------------------------------------------
// 五、Template 延伸挑戰題 (固定題型)
// ---------------------------------------------------------
template <class T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

template <class T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}

// ---------------------------------------------------------
// 系統功能實作
// ---------------------------------------------------------

// 功能 1：新增學生資料
void addStudent(map<string, Student>& students) {
    string id, name;
    int score;

    cout << "\n[新增學生資料]\n";
    cout << "請輸入學號: ";
    cin >> id;

    // 檢查學號是否重複
    if (students.find(id) != students.end()) {
        cout << "⚠️ 錯誤：學號 " << id << " 已存在，拒絕新增。\n";
        return;
    }

    cout << "請輸入姓名: ";
    cin >> name;
    cout << "請輸入成績 (0-100): ";
    cin >> score;

    if (score < 0 || score > 100) {
        cout << "⚠️ 錯誤：成績必須介於 0 到 100 之間。\n";
        return;
    }

    students[id] = {id, name, score};
    cout << "✅ 學生 " << name << " 資料新增成功！\n";
}

// 功能 2：列出所有學生
void listAllStudents(const map<string, Student>& students) {
    cout << "\n[所有學生列表]\n";
    if (students.empty()) {
        cout << "目前無任何學生資料。\n";
        return;
    }

    cout << left << setw(15) << "學號" << setw(15) << "姓名" << "成績\n";
    cout << "------------------------------------------\n";
    for (const auto& pair : students) {
        cout << left << setw(15) << pair.second.id 
             << setw(15) << pair.second.name 
             << pair.second.score << "\n";
    }
}

// 功能 3：依成績排序 (使用 vector 與 sort)
void sortByScore(const map<string, Student>& students) {
    cout << "\n[依成績排序 (高到低)]\n";
    if (students.empty()) {
        cout << "目前無任何學生資料。\n";
        return;
    }

    // 將資料從 map 轉移到 vector 以便排序
    vector<Student> sorted_students;
    for (const auto& pair : students) {
        sorted_students.push_back(pair.second);
    }

    // 使用 C++11 Lambda expression 進行自訂排序
    sort(sorted_students.begin(), sorted_students.end(), [](const Student& a, const Student& b) {
        return a.score > b.score; 
    });

    cout << left << setw(15) << "學號" << setw(15) << "姓名" << "成績\n";
    cout << "------------------------------------------\n";
    for (const auto& student : sorted_students) {
        cout << left << setw(15) << student.id 
             << setw(15) << student.name 
             << student.score << "\n";
    }
}

// 功能 4：查詢學生
void searchStudent(const map<string, Student>& students) {
    string id;
    cout << "\n[查詢學生]\n";
    cout << "請輸入要查詢的學號: ";
    cin >> id;

    auto it = students.find(id);
    if (it != students.end()) {
        cout << "✅ 找到學生資料：\n";
        cout << "學號: " << it->second.id << "\n"
             << "姓名: " << it->second.name << "\n"
             << "成績: " << it->second.score << "\n";
    } else {
        cout << "⚠️ 查無此學號。\n";
    }
}

// 功能 5：統計成績 (整合 Template Function)
void showStatistics(const map<string, Student>& students) {
    cout << "\n[成績統計]\n";
    if (students.empty()) {
        cout << "目前無任何學生資料可供統計。\n";
        return;
    }

    int total_score = 0;
    int max_score = -1;
    int min_score = 101;
    int pass_count = 0;
    int fail_count = 0;

    for (const auto& pair : students) {
        int current_score = pair.second.score;
        total_score += current_score;

        // 呼叫規定要求的 Template Function
        max_score = getMax<int>(max_score, current_score);
        min_score = getMin<int>(min_score, current_score);

        if (current_score >= 60) {
            pass_count++;
        } else {
            fail_count++;
        }
    }

    double average = static_cast<double>(total_score) / students.size();

    cout << "總人數 : " << students.size() << "\n";
    cout << "全班平均: " << fixed << setprecision(2) << average << "\n";
    cout << "最高分 : " << max_score << "\n";
    cout << "最低分 : " << min_score << "\n";
    cout << "及格人數: " << pass_count << "\n";
    cout << "不及格數: " << fail_count << "\n";
}

int main() {
    // 使用 map 作為主要儲存結構，以學號 (string) 為 key
    map<string, Student> students;
    int choice = -1;

    while (choice != 0) {
        cout << "\n=== 學生成績管理系統 ===\n";
        cout << "1. Add student\n";
        cout << "2. List all students\n";
        cout << "3. Sort by score\n";
        cout << "4. Search by id\n";
        cout << "5. Show statistics\n";
        cout << "0. Exit\n";
        cout << "========================\n";
        cout << "請輸入選項: ";
        
        if (!(cin >> choice)) {
            cout << "輸入錯誤，請輸入數字。\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: listAllStudents(students); break;
            case 3: sortByScore(students); break;
            case 4: searchStudent(students); break;
            case 5: showStatistics(students); break;
            case 0: cout << "系統結束，再見！\n"; break;
            default: cout << "無效的選項，請重新輸入。\n"; break;
        }
    }

    return 0;
}