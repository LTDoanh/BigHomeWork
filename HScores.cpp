#include "HScores.h"

std::vector<Player> HScores::read_high_scores() {
    // Tạo một vector rỗng để lưu kết quả
    std::vector<Player> result;

    // Mở file để đọc
    file.open(FILENAME, ios::in);

    // Kiểm tra xem file có mở được không
    if (file.is_open()) {
        // Đọc từng dòng trong file
        string line;
        while (getline(file, line)) {
            // Tạo một đối tượng player để lưu dữ liệu
            Player p;

            // Tìm vị trí của dấu cách đầu tiên trong dòng
            int pos1 = line.find('/');

            // Lấy tên của player từ đầu dòng đến dấu cách
            p.name = line.substr(0, pos1);

            int pos2 = line.rfind('/');

            // Lấy điểm của player từ sau dấu cách đến cuối dòng
            p.score = stoi(line.substr(pos1 + 1, pos2));

            // Thêm player vào vector kết quả
            result.push_back(p);
        }

        // Đóng file
        file.close();
    }
    else {
        // Nếu file không mở được, in ra thông báo lỗi
        cout << "Cannot open file " << FILENAME << endl;
    }

    // Trả về vector kết quả
    return result;
}

void HScores::write_high_scores(string newname, int newscore, std::vector<Player> &highScores)
{
    // Tạo một đối tượng player để lưu dữ liệu
    Player p;
    p.name = newname;
    p.score = newscore;

    // Thêm điểm của người chơi vào vector
    highScores.push_back(p);

    // Sắp xếp lại theo điểm theo thứ tự giảm dần
    sort(highScores.begin(), highScores.end(), [](const Player& a, const Player& b) {
        return a.score > b.score;
    });

    // Nếu vector có nhiều hơn 5 phần tử, xóa phần tử cuối cùng
    if (highScores.size() > 5) {
        highScores.pop_back();
    }

    // Mở file và ghi lại các số vào file
    file.open(FILENAME, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "Cannot open file " << FILENAME << endl;
        return;
    }
    for (Player i : highScores) {
        file << i.name << "/" << i.score << "/" << endl;
    }
    file.close();
}

// Hàm kiểm tra xem điểm của người chơi có nằm trong top không
bool HScores::is_high_score(int newscore, std::vector<Player> highScores)
{
    if (highScores.size() < 5 || newscore > highScores.back().score) {
        return true;
    }
    return false;
}
