#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

const unsigned char JPEG_HEADER[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46};
const unsigned char JPEG_FOOTER[] = {0xFF, 0xD9, 0x00, 0x00};

class JPEGExtractor {
private:
    vector<unsigned char> buffer;
    int extractedCount = 0;
    vector<pair<size_t, size_t>> positions;

    bool compareSequence(size_t position, const unsigned char* pattern, size_t patternLength) {
        if (position + patternLength > buffer.size()) return false;
        for (size_t idx = 0; idx < patternLength; idx++) {
            if (buffer[position + idx] != pattern[idx]) return false;
        }
        return true;
    }

    void saveImage(size_t begin, size_t finish, const string& fname) {
        ofstream outFile(fname, ios::binary);
        if (outFile) {
            outFile.write(reinterpret_cast<const char*>(&buffer[begin]), finish - begin);
            outFile.close();
        }
    }

    void saveTextGrid() {
        const size_t blockSize = 512 * 64;
        size_t totalBlocks = buffer.size() / blockSize + (buffer.size() % blockSize != 0);
        vector<char> grid(totalBlocks, '.');

        for (const auto& pos : positions) {
            size_t startBlock = pos.first / blockSize;
            size_t endBlock = (pos.second - 1) / blockSize;
            for (size_t i = startBlock; i <= endBlock && i < grid.size(); ++i) {
                grid[i] = 'X';
            }
        }

        ofstream viz("pozice_viz.txt");
        const int width = 64;
        for (size_t i = 0; i < grid.size(); ++i) {
            viz << grid[i];
            if ((i + 1) % width == 0) viz << '\n';
        }
        viz << '\n';
        viz.close();
    }

    void saveBenchmark(double mbPerSecond) {
        ofstream out("benchmark.txt");
        out << "Rychlost zpracování: " << fixed << mbPerSecond << " MB/s\n";
        out << "Způsob měření: std::chrono + velikost bufferu / čas zpracování\n";
        out.close();
    }

public:
    bool loadFile(const string& source) {
        ifstream inFile(source, ios::binary);
        if (!inFile) {
            cout << "Failed to open input file!" << endl;
            return false;
        }

        buffer.assign(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>());
        inFile.close();
        return true;
    }

    void extractImagesWithBenchmark() {
        auto startTime = high_resolution_clock::now();

        size_t currentPos = 0;

        while (currentPos < buffer.size()) {
            if (compareSequence(currentPos, JPEG_HEADER, sizeof(JPEG_HEADER))) {
                size_t imgStart = currentPos;
                currentPos += sizeof(JPEG_HEADER);

                while (currentPos < buffer.size() &&
                       !compareSequence(currentPos, JPEG_FOOTER, sizeof(JPEG_FOOTER))) {
                    currentPos++;
                }

                if (currentPos + sizeof(JPEG_FOOTER) <= buffer.size()) {
                    size_t imgEnd = currentPos + sizeof(JPEG_FOOTER);
                    positions.push_back({imgStart, imgEnd});
                    string outputName = "output_" + to_string(extractedCount++) + ".jpg";
                    saveImage(imgStart, imgEnd, outputName);
                    currentPos = imgEnd;
                }
            } else {
                currentPos++;
            }
        }

        auto endTime = high_resolution_clock::now();
        duration<double> durationSeconds = endTime - startTime;

        double megaBytes = buffer.size() / (1024.0 * 1024.0);
        double speed = megaBytes / durationSeconds.count();

        saveTextGrid();
        saveBenchmark(speed);
    }
};

int main() {
    JPEGExtractor extractor;
    if (!extractor.loadFile("bad_disk.img")) {
        return 1;
    }

    extractor.extractImagesWithBenchmark();
    return 0;
}
