#include "AdditionalAlgorithm.h"
#include <math.h>

bool AdditionalAlgorithm::hasDuplicates(int* a, int b) {
	int* seen = new int[b];
	for (int i = 0; i < b; i++) {
		if (contains(seen, b, a[i]) && a[i] > -1) return true;
		seen[i] = a[i];
	}
	return false;
}

bool AdditionalAlgorithm::contains(int* a, int b, int c) {
	for (int i = 0; i < b; i++) {
		if (a[i] == c) return true;
	}
	return false;
}

AdditionalAlgorithm::AdditionalAlgorithm(int rows, int cols, int** table) {
	this->rows = rows;
	this->cols = cols;
	this->table = table;
}

AdditionalAlgorithm::~AdditionalAlgorithm() {

}

int AdditionalAlgorithm::findMaxSum() {
	int size = 0;
	int*** tmpTable = nullptr;
	if (rows <= cols) {
		size = (int)pow(cols, rows);
		tmpTable = new int** [rows];
		for (int i = 0; i < rows; i++) {
			tmpTable[i] = new int* [static_cast<int>(size) * sizeof(int*)];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < size; j++) {
				tmpTable[i][j] = new int[3];
			}
		}
	}
	else {
		size = (int)pow(rows, cols);
		tmpTable = new int** [rows];
		for (int i = 0; i < rows; i++) {
			tmpTable[i] = new int* [static_cast<int>(size) * sizeof(int*)];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < size; j++) {
				tmpTable[i][j] = new int[3];
			}
		}
		int** tmp = new int* [cols];
		for (int i = 0; i < cols; i++) {
			tmp[i] = new int[rows];
		}
		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++) {
				tmp[i][j] = table[j][i];
			}
		}
		table = tmp;
		int x = cols;
		cols = rows;
		rows = x;

	}
	for (int i = 0; i < rows; i++) {
		int counter = 0;
		for (int j = 0; j < pow(cols, i + 1); j++) {
			for (int k = 0; k < pow(cols, rows - i - 1); k++) {
				tmpTable[i][counter][0] = j % cols;
				tmpTable[i][counter][1] = i;
				tmpTable[i][counter][2] = table[i][j % cols];
				counter++;
			}
		}
	}
	int max = 0;
	for (int j = 0; j < size; j++) {
		int sum = 0;
		int* takenCols = new int[cols];
		for (int i = 0; i < cols; i++) takenCols[i] = -1;
		int counter = 0;
		bool reset = false;
		for (int i = 0; i < rows; i++) {
			sum += tmpTable[i][j][2];
			takenCols[counter] = tmpTable[i][j][0];
			counter++;
		}
		if (hasDuplicates(takenCols, cols)) sum = 0;
		if (sum > max) max = sum;
		delete[] takenCols;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < size; j++) {
			delete[] tmpTable[i][j];
		}
		delete[] tmpTable[i];
	}
	delete[] tmpTable;
	return max;
}
