#include "Matrix4f.h"

Matrix4f::Matrix4f(float a2[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            this->m_matrix[i][j] = a2[i][j];
        }
    }
}

Matrix4f::Matrix4f() {
    
}