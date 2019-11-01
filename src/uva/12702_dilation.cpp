/*********************************************************************
Dilation
--------
UVa ID: 127 02

Morphological image processing is a collection of non-linear operations
related to the shape or morphology of features in an image. One of the
most basic morphological operations is dilation. Dilation adds pixels
to the boundaries of objects in an image. The number of pixels added
to the objects in an image depends on the size and shape of the
structuring element used to process the image. A structuring element
is a shape mask used in the basic morphological operations. They can
be of any shape and size that is digitally representable, and each has
an origin. The matrix dimensions specify the size of the structuring
element and the pattern of ones and zeros specifies the shape of the
structuring element. In this task the size of the structuring element
is square i.e. 2x2, 3x3, or 4x4 etc. and can be of any shape. The
morphological functions use the following code to get the coordinates
of the origin of structuring elements of any size and dimension:
	origin = floor(size(structuring_element) / 2).
If structuring element matrix is [0 1 0; 1 1 1; 0 1 0], then,
	size(structuring_element) = 3x3,
so, origin = (1, 1). Dilate (B, S) takes binary image B, places the
origin of the structuring element S over each 1-pixel, and ORs the
structuring element S into the output image at the corresponding
position.

Input
-----
First line of the input file is an integer T (T < 25) which denotes
how many sets of inputs are there. Each test case starts with the
dimensions of the binary image mXn, where m (2 <= m <= 100) is
the number of rows and n (2 <= n <= 100) is the number of columns.
Followed by the binary image which contains only '0' or '1'. Then
followed by the dimensions of the structuring element qXr, where
q (1 <= q <= 10) is the number of rows and r (1 <= r <= 10) is
the number of columns and then followed by the structuring element.
Size of structuring element will be less than or equal to binary
image (q <= n, r <= m). In input binary image border lines will
not contain any 1s.

Output
------
For each test case print the binary image after dilation process.
In output there should be no blank space after the end of a line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>

template<typename T>
void apply(Matrix<T>& image, const Matrix<T>& element, std::size_t i_row, std::size_t i_col)
{
	const auto c_row = element.rows() / 2;
	const auto c_col = element.cols() / 2;

	const auto first_drow = -static_cast<std::ptrdiff_t>(std::min(c_row, i_row));
	const auto first_dcol = -static_cast<std::ptrdiff_t>(std::min(c_col, i_col));

	const auto last_drow =
		static_cast<std::ptrdiff_t>(std::min(element.rows() - c_row, image.rows() - i_row));
	const auto last_dcol =
		static_cast<std::ptrdiff_t>(std::min(element.cols() - c_col, image.cols() - i_col));

	for (auto dcol = first_dcol; dcol < last_dcol; ++dcol)
		for (auto drow = first_drow; drow < last_drow; ++drow)
			if (element(c_row + drow, c_col + dcol) == 1)
				image(i_row + drow, i_col + dcol) |= 2;
}

template<typename T>
void dilate(Matrix<T>& image, const Matrix<T>& _element)
{
	for (std::size_t col = 0; col < image.cols(); ++col)
		for (std::size_t row = 0; row < image.rows(); ++row)
			if ((image(row, col) & 1) == 1)
				apply(image, _element, row, col);

	for (std::size_t col = 0; col < image.cols(); ++col)
		for (std::size_t row = 0; row < image.rows(); ++row)
			image(row, col) = (image(row, col) != 0);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t rows;
		std::size_t cols;

		read(rows, cols);
		image_.resize(rows, cols);
		read_matrix(image_);

		read(rows, cols);
		element_.resize(rows, cols);
		read_matrix(element_);
	}

	virtual void solve(unsigned int i_case) override
	{
		dilate(image_, element_);

		write_ln("Case ", i_case, ":");
		write_matrix(image_);
	}

private:
	Matrix<unsigned int> image_;
	Matrix<unsigned int> element_;
};

MAIN
