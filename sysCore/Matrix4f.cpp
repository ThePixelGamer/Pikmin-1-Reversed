#include "Matrix4f.h"

Matrix4f::Matrix4f(float a2[4][4]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            this->m_matrix[i][j] = a2[i][j];
        }
    }
}

Matrix4f::Matrix4f() {}

void Matrix4f::blend(Matrix4f& a2, float a3) { //pseudocode fine, asm not
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            this->m_matrix[i][j] = (a2.m_matrix[i][j] - this->m_matrix[i][j]) * a3 + this->m_matrix[i][j];
        }
    }
}

void Matrix4f::getColumn(int a2, Vector3f& a3) {
    a3.set(m_matrix[a2][0], m_matrix[a2][1], m_matrix[a2][2]);
}

void Matrix4f::getRow(int a2, Vector3f& a3) {
    a3.set(m_matrix[a2][0], m_matrix[a2+1][0], m_matrix[a2+2][0]);
}