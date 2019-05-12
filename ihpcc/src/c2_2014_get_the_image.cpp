/*********************************************************************
Get the image
-------------
ID: C2 (2014)

Gru orders his minions to generate the image as per the following
rules. Each image comprises of width * height pixels. This represents
a rectangular complex plane where each pixel has a complex value z0.
For each pixel you begin an iteration z(n + 1) = z(n)^2 + z(0), where
z(0) is the complex point. This iteration is performed as long as the
computed values or the initial value of |z| is less than R, where R
denotes the escape radius and is given as an input. The upper limit
of the number of iterations to be performed is given by an integer
Iter_max. If a pixel reaches maximum iteration then it acquires the
grayscale value 0 (black) else 255 (white).

Input
-----
The input consists of 8 parameter: Integer width (2 <= width <= 5'000),
height (2 <= height <= 5'000), Real Zx(Min), Zx(Max) - minimum and
maximum value of pixels on the real axis, Zy(Min), Zy(Max) - minimum
and maximum value of pixels on the imaginary axis. The maximum
iteration limit is given by an integer Iter_max (<= 1'000), R is a
real value (<= 10.0). All the above input are space separated in a
single line.

Output
------
Print the image matrix.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base_mpi.hpp"
#include <algorithm>
#include <cassert>
#include <complex>
#include <cstddef>
#include <thread>
#include <vector>

using T = unsigned char;

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		read(width_, height_, x_min_, x_max_, y_min_, y_max_, max_iters_, r_);
	}

	virtual void solve_master() override
	{
		mpi_bcast(width_, height_, x_min_, x_max_, y_min_, y_max_, max_iters_, r_);

		std::vector<T> image(width_ * height_, 9);
		compute_image_part(image, mpi_size_);

		auto image_part_type = mpi_create_padded_block_type<T>(width_, width_ * mpi_size_);
		for (auto r = 1u; r < mpi_size_; ++r)
		{
			const auto size_y = get_size_y(r);
			mpi_recv(image.data() + width_ * r, size_y, r, image_part_type);
		}

		mpi_type_free(image_part_type);

		for (auto it = image.begin(); it != image.end(); it += width_)
		{
			write_range(
				it, it + width_, [](auto v) { return +v; }, ' ');
			write_ln();
		}
	}

	virtual void solve_slave() override
	{
		mpi_bcast(width_, height_, x_min_, x_max_, y_min_, y_max_, max_iters_, r_);

		std::vector<T> image(width_ * get_size_y(mpi_rank_));
		compute_image_part(image);

		mpi_send(image.data(), image.size(), 0);
	}

	void compute_image_part(std::vector<unsigned char>& image, std::size_t stride = 1)
	{
		const auto dx = (x_max_ - x_min_) / (width_ - 1);
		const auto dy = (y_max_ - y_min_) / (height_ - 1);

		const auto size_y = get_size_y(mpi_rank_);
		const auto n_threads = std::thread::hardware_concurrency();
		const auto n_max_per_thread = (size_y + n_threads - 1) / n_threads;

		const auto worker = [this, dx, dy, stride, &image](std::size_t y, std::size_t y_max) {
			for (; y < y_max; ++y)
				for (std::size_t x = 0; x < width_; ++x)
				{
					const auto zx = x_min_ + dx * x;
					const auto zy = y_min_ + dy * (y * mpi_size_ + mpi_rank_);
					image[width_ * stride * y + x] = is_in_mandelbrot_set({zx, zy});
				}
		};

		std::vector<std::thread> workers;
		for (std::size_t y = 0; y < size_y; y += n_max_per_thread)
		{
			const auto block_size_y = std::min(n_max_per_thread, size_y - y);
			workers.emplace_back(worker, y, y + block_size_y);
		}

		for (auto& w : workers)
			w.join();
	}

	std::size_t get_size_y(unsigned int rank) const
	{
		return height_ / mpi_size_ + (rank < height_ % mpi_size_);
	}

	bool is_in_mandelbrot_set(const std::complex<double> z0) const
	{
		unsigned int it = 0;
		auto z = z0;
		while (std::abs(z) < r_)
		{
			z = z * z + z0;
			if (++it >= max_iters_)
				return true;
		}

		return false;
	}

private:
	std::size_t width_;
	std::size_t height_;

	double x_min_, x_max_;
	double y_min_, y_max_;

	unsigned int max_iters_;
	double r_;
};

MAIN
