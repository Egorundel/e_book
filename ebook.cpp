#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : user_page_counts_(MAX_USER_COUNT_ + 1, -1)
        ,  // -1 значит, что не случилось ни одного READ
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {
    }

    void Read(int user_id, int page_count) {
        UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
        user_page_counts_[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        const int pages_count = user_page_counts_[user_id];
        if (pages_count == -1) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Один из простых способов сделать это — умножить его на 1.0.
        return 1.0 - (page_achieved_by_count_[pages_count] - 1.0) / (user_count - 1.0);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    // Номер страницы, до которой дочитал пользователь <ключ>
    vector<int> user_page_counts_;
    // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
    vector<int> page_achieved_by_count_;

    int GetUserCount() const {
        return page_achieved_by_count_[0];
    }

    void UpdatePageRange(int lhs, int rhs) {
        for (int i = lhs; i < rhs; ++i) {
            ++page_achieved_by_count_[i];
        }
    }
};

int main() {
    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; query_id++) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ"s) {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER"s) {
            cout << setprecision(6) << manager.Cheer(user_id) << endl;
        }
    }
}