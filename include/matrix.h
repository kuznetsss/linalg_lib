
namespace linalg {

template<size_t num_rows, size_t num_columns, typename T>
class Matrix {};

template<size_t num_rows, typename T>
class Vector : public Matrix<num_rows, 1, T> {};

}
