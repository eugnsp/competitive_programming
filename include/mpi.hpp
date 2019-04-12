#pragma once
#include <mpi.h>
#include <vector>

template<typename T>
struct Data_type;

template<>
struct Data_type<int>
{
	static constexpr auto value = MPI_INT;
};

template<>
struct Data_type<unsigned int>
{
	static constexpr auto value = MPI_UNSIGNED;
};

template<>
struct Data_type<unsigned long>
{
	static constexpr auto value = MPI_UNSIGNED_LONG;
};

template<>
struct Data_type<unsigned long long>
{
	static constexpr auto value = MPI_UNSIGNED_LONG_LONG;
};

template<typename T>
auto get_data_type(const T&)
{
	return Data_type<T>::value;
}

template<typename T>
void mpi_bcast(T* buff, std::size_t count)
{
	MPI_Bcast(buff, static_cast<int>(count), get_data_type(*buff),
		0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_send(const T* buff, std::size_t count, int dest)
{
	MPI_Send(buff, static_cast<int>(count), get_data_type(*buff),
		dest, 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_recv(T* buff, std::size_t count, int source)
{
	MPI_Recv(buff, static_cast<int>(count), get_data_type(*buff),
		source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

template<typename T>
void mpi_scatterv_send(
	const T* buff, const std::vector<int>& sizes, const std::vector<int>& offsets)
{
	MPI_Scatterv(const_cast<T*>(buff), sizes.data(), offsets.data(), get_data_type(*buff),
		MPI_IN_PLACE, 0, get_data_type(*buff), 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_scatterv_recv(T* buff, std::size_t size)
{
	MPI_Scatterv(nullptr, nullptr, nullptr, get_data_type(*buff),
		buff, static_cast<int>(size), get_data_type(*buff), 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_gatherv_send(const T* buff, std::size_t size)
{
	MPI_Gatherv(const_cast<T*>(buff), static_cast<int>(size), get_data_type(*buff),
		nullptr, nullptr, nullptr, get_data_type(*buff), 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_gatherv_recv(T* buff, const std::vector<int>& sizes, const std::vector<int>& offsets)
{
	MPI_Gatherv(MPI_IN_PLACE,0, get_data_type(*buff),
		buff, sizes.data(), offsets.data(), get_data_type(*buff), 0, MPI_COMM_WORLD);
}
