#pragma once
class AdditionalAlgorithm {
	int rows;
	int cols;
	int** table;
	bool hasDuplicates(int* a, int b);
	bool contains(int* a, int b, int c);
public:
	AdditionalAlgorithm(int rows, int cols, int** table);
	~AdditionalAlgorithm();
	int findMaxSum();
};