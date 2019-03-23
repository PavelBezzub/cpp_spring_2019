class Matrix
{
	class proxy
	{
	public:
		proxy() :arr(NULL), size(0) {}
		~proxy() { delete[](arr); }
		void init(int columns);
		proxy(proxy& a)
		{
			size = a.size;
			arr = new int[a.size];
			for (int i = 0; i < size; i++) {
				arr[i] = a.arr[i];
			}
		}
		void copy(proxy &a) {
			arr = new int[a.size];
			for (int i = 0; i < a.size; i++) {
				arr[i] = a.arr[i];
			}
			size = a.size;
		}
		const int& operator[](int index) const;
		int& operator[](int index);
	private:
		int size;
		int *arr;
	};
public:
	Matrix(int row, int columns);
	~Matrix();
	Matrix  operator*=(int x);
	const bool operator==(const Matrix& other);
	const bool operator!=(const Matrix& other);
	const proxy& operator[](int index) const;
	proxy& operator[](int index);
	Matrix(Matrix& a) {
		row = a.row;
		M_matrix = new proxy[a.row];
		for (int i = 0; i < a.row; i++) {
			M_matrix[i].copy(a.M_matrix[i]);
		}

	}
	int getRows();
	int getColumns();

private:
	proxy *M_matrix;
	int row;
	int columns;
};
void Matrix::proxy::init(int columns)
{
	arr = new int[columns];
	size = columns;
}
const int& Matrix::proxy::operator[](int index) const
{   
	if (index >= size) throw std::out_of_range("");
	return arr[index];
}
int& Matrix::proxy::operator[](int index)  
{
	if (index >= size) throw std::out_of_range("");
	return arr[index];
}

const Matrix::proxy& Matrix::operator[](int index) const{
	if (index >= row) throw std::out_of_range("");
	return M_matrix[index];
}
Matrix::proxy& Matrix::operator[](int index)  {
	if (index >= row) throw std::out_of_range("");
	return M_matrix[index];
}

Matrix::Matrix(int rows, int column): row(rows), columns(column)
{   
	M_matrix = new proxy[row];
	for (int i = 0; i < row; i++)
	{
		M_matrix[i].init(columns);
	}
}
Matrix::~Matrix()
{
	delete[](M_matrix);
}

int Matrix::getRows() {
	return row;
}

int Matrix::getColumns() {
	return columns; 
}

Matrix  Matrix::operator*=(int x) {
	for (int i =0; i < row;i++ )
		for (int j = 0; j < columns; j++)
		{
			M_matrix[i][j] = M_matrix[i][j] * x;
		}
	
	Matrix M2(*this);
	return M2;
}

const bool Matrix::operator==(const Matrix& other) {
    if ( (columns != other.columns) || (row != other.row)) return false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < columns; j++)
		{
			if (M_matrix[i][j] != other.M_matrix[i][j]) return false;
		}
	}
	return true;
}
const bool Matrix::operator!=(const Matrix& other) {
	if ((columns != other.columns) || (row != other.row)) return true;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < columns; j++)
		{
			if (M_matrix[i][j] != other.M_matrix[i][j]) return true;
		}
	}
	return false;
}
