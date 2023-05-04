// Khai báo các thư viện cần thiết
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Hàm để lưu lại điểm và tên của 5 người cao nhất
void save_high_scores(int score, string name) {
    // Mở tệp high_scores.txt để đọc và ghi dữ liệu
    fstream file("high_scores.txt", ios::in||ios::out);
    // Kiểm tra xem tệp có mở được không
    if (!file) {
        cout << "Không thể mở tệp high_scores.txt\n";
        return;
    }
    // Tạo một mảng để lưu trữ điểm và tên của 5 người cao nhất
    int scores[5] = {0};
    string names[5] = {""};
    // Đọc dữ liệu từ tệp và lưu vào mảng
    for (int i = 0; i < 5; i++) {
        file >> scores[i] >> names[i]);
    }
    // Tìm vị trí thấp nhất trong mảng
    int min_index = 0;
    int min_score = scores[0];
    for (int i = 0; i < 5; i++) {
        if (scores[i] < min_score) {
            min_index = i;
            min_score = scores[i];
        }
    }
    // Kiểm tra xem điểm của người chơi có cao hơn điểm thấp nhất trong mảng không
    if (score > min_score) {
        // Thay thế điểm và tên thấp nhất bằng điểm và tên của người chơi
        scores[min_index] = score;
        names[min_index] = name;
        // Sắp xếp mảng theo thứ tự giảm dần của điểm
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 5; j++) {
                if (scores[i] < scores[j]) {
                    swap(scores[i], scores[j]);
                    swap(names[i], names[j]);
                }
            }
        }
        // Quay lại đầu tệp
        file.seekg(0);
        // Ghi lại dữ liệu vào tệp
        for (int i = 0; i < 5; i++) {
            file << scores[i] << " " << names[i] << "\n";
        }
    }
    // Đóng tệp
    file.close();
}

// Hàm để lưu lại điểm và tên của 5 người cao nhất
void save_high_scores(int score, string name) {
    // Mở tệp high_scores.txt để ghi dữ liệu
    ofstream outfile("high_scores.txt", ios::app);
    // Kiểm tra xem tệp có mở được không
    if (!outfile) {
        cout << "Không thể mở tệp high_scores.txt\n";
        return;
    }
    // Ghi điểm và tên vào tệp
    outfile << score << " " << name << "\n";
    // Đóng tệp
    outfile.close();
}

// Hàm để hiển thị 5 người cao nhất từ tệp high_scores.txt
void show_high_scores() {
    // Mở tệp high_scores.txt để đọc dữ liệu
    ifstream infile("high_scores.txt");
    // Kiểm tra xem tệp có mở được không
    if (!infile) {
        cout << "Không thể mở tệp high_scores.txt\n";
        return;
    }
    // Tạo một mảng để lưu trữ điểm và tên của 5 người cao nhất
    int scores[5] = {0};
    string names[5] = {""};
    // Đọc dữ liệu từ tệp và cập nhật mảng nếu điểm cao hơn
    int score;
    string name;
    while (infile >> score >> name) {
        // Tìm vị trí thấp nhất trong mảng
        int min_index = 0;
        int min_score = scores[0];
        for (int i = 1; i < 5; i++) {
            if (scores[i] < min_score) {
                min_index = i;
                min_score = scores[i];
            }
        }
        // Nếu điểm đọc được cao hơn điểm thấp nhất trong mảng, thay thế nó
        if (score > min_score) {
            scores[min_index] = score;
            names[min_index] = name;
        }
    }
    // Đóng tệp
    infile.close();
    // Sắp xếp mảng theo thứ tự giảm dần của điểm
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (scores[i] < scores[j]) {
                swap(scores[i], scores[j]);
                swap(names[i], names[j]);
            }
        }
    }
    // Hiển thị mảng ra màn hình
    cout << "Diem cao nhat:\n";
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << names[i] << " - " << scores[i] << "\n";
    }
}

// Hàm chính để chạy trò chơi
int main() {
    // Khởi tạo biến ngẫu nhiên bằng thời gian hiện tại
    srand(time(0));

    // Tạo một số ngẫu nhiên từ 1 đến 10
    int secret_number = rand() % 10 + 1;

    // Tạo biến để lưu trữ số đoán và số lần đoán của người chơi
    int guess;
    int tries = 0;

    // Tạo biến để lưu trữ tên của người chơi
    string player_name;

    // Hiển thị lời chào và hướng dẫn cho người chơi
    cout << "Chao mung ban den voi tro choi doan so ngau nhien!\n";
    cout << "Toi da nghi ra mot so tu 1 den 10.\n";
    cout << "Ban co the doan duoc so do khong?\n";
    cout << "Ban se co 10 diem voi moi luot doan dung.\n";
    cout << "Hay nhap ten cua ban truoc khi bat dau:\n";
    cin >> player_name;

    // Lặp lại cho đến khi người chơi đoán đúng hoặc hết lượt
    do {
        // Tăng số lần đoán lên 1
        tries++;

        // Nhập số đoán từ bàn phím
        cout << "Lan doan thu " << tries << ": ";
        cin >> guess;

        // Kiểm tra xem số đoán có hợp lệ không
        if (guess < 1 || guess > 10) {
            cout << "So do khong nam trong khoang tu 1 den 10.\n";
            cout << "Hay thu lai.\n";
            continue; // Bỏ qua các câu lệnh sau và quay lại vòng lặp
        }

        // Kiểm tra xem số đoán có bằng số bí mật không
        if (guess == secret_number) {
            cout << "Chuc mung! Ban da doan dung!\n";
            break; // Thoát khỏi vòng lặp
        }
        else if (guess < secret_number) {
            cout << "So do qua nho.\n";
            cout << "Hay thu lai.\n";
        }
        else {
            cout << "So do qua lon.\n";
            cout << "Hay thu lai.\n";
        }
    } while (tries < 10); // Lặp lại cho đến khi hết 10 lần

    // Kiểm tra xem người chơi có thắng hay không
    if (guess == secret_number) {
        // Tính điểm của người chơi
        int score = 10 * (11 - tries);
        // Hiển thị điểm của người chơi
        cout << "Ban da duoc " << score << " diem.\n";
        // Lưu lại điểm và tên của người chơi vào tệp high_scores.txt
        save_high_scores(score, player_name);
    }
    else {
        // Hiển thị thông báo thua cuộc
        cout << "Ban da het luot doan.\n";
        cout << "So bi mat la: " << secret_number << "\n";
        cout << "Ban khong duoc diem nao.\n";
    }

    // Hiển thị 5 người cao nhất từ tệp high_scores.txt
    show_high_scores();

    // Kết thúc chương trình
    return 0;
}
