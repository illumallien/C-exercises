#include <iostream>
#include <vector>

using namespace std;

class Matrix {
private:
    vector<vector<int>> mat;
    int size;

public:
    // Constructor
    Matrix(int n) : size(n), mat(n, vector<int>(n)) {}

    // Input method
    void input() {
        cout << "Enter the elements of the " << size << "x" << size << " matrix row by row:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cin >> mat[i][j];
            }
        }
    }

    // Operator overloading for addition
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.mat[i][j] = this->mat[i][j] + other.mat[i][j];
            }
        }
        return result;
    }

    // Operator overloading for subtraction
    Matrix operator-(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                result.mat[i][j] = this->mat[i][j] - other.mat[i][j];
            }
        }
        return result;
    }

    // Operator overloading for multiplication
    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    result.mat[i][j] += this->mat[i][k] * other.mat[k][j];
                }
            }
        }
        return result;
    }

    // Method to print the matrix
    void print() const {
        for (const auto& row : mat) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter the size of the matrices (n x n): ";
    cin >> n;

    cout << "Input first matrix:\n";
    Matrix mat1(n);
    mat1.input();

    cout << "Input second matrix:\n";
    Matrix mat2(n);
    mat2.input();

    cout << "Matrix Addition Result:\n";
    Matrix sum = mat1 + mat2;
    sum.print();

    cout << "Matrix Subtraction Result:\n";
    Matrix difference = mat1 - mat2;
    difference.print();

    cout << "Matrix Multiplication Result:\n";
    Matrix product = mat1 * mat2;
    product.print();

    return 0;
}
