#include <iostream>
#include <vector>
using namespace std;

class Matrix{
    private:
        int size;
        vector<vector<int>> mat;

    public:
        Matrix(int n) 
        :size(n), mat(n, vector<int>(n)){}  

        ~Matrix(){}

        void doldur(){
            for(int i=0;i<size;i++){
                for(int k=0; k<size; k++){
                    cin>>mat[i][k];
                }
            }    
       
        }

        void print() const{
            cout << "matrisiniz:" << endl;
            for(int i=0;i<size;i++){
                for(int k=0; k<size; k++){
                    cout << " " << mat[i][k] <<" ";
                }
                cout << endl;
            } 
        }

        Matrix operator+(const Matrix &added) const{
            Matrix addition(size);
            for(int i=0;i<size;i++){
                for(int k=0; k<size; k++){
                    addition.mat[i][k]=mat[i][k]+added.mat[i][k];
                }
            }     
            return addition;  
        }


        Matrix operator-(const Matrix &sub) const{
            Matrix substraction(size);
            for(int i=0;i<size;i++){
                for(int k=0; k<size; k++){
                    substraction.mat[i][k]=mat[i][k]-sub.mat[i][k];
                }
            }     
            return substraction;   

        }

        Matrix operator*(const Matrix& other) const{
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

};


int main(){
    int size;
    cout<< "matris boyutu girin" << endl;
    cin >>size;
    Matrix matrix1(size);
    Matrix matrix2(size);
    cout << "ilk matrisi girin." << endl;
    matrix1.doldur();
    matrix1.print();
    cout << "ikinci matrisi girin." << endl;
    matrix2.doldur();
    matrix2.print();
    Matrix sum= matrix1+matrix2; 
    cout << "Matris1 + Matris2 :" << endl;
    sum.print();
    Matrix substraction = matrix1-matrix2;
    cout << "Matris1 - Matris2 :" << endl;
    substraction.print();
    Matrix product = matrix1*matrix2;
    cout << "Matris1 * Matris2 :" << endl;
    product.print();


    


    



    return 0;
}