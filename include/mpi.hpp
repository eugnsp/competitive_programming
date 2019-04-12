#pragma once
#include <mpi.h>

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
void mpi_bcast(T* value, std::size_t count, int root = 0)
{
	MPI_Bcast(value, static_cast<int>(count), get_data_type(*value),
		root, MPI_COMM_WORLD);
}

template<typename T>
void mpi_send(const T* value, std::size_t count, int dest)
{
	MPI_Send(value, static_cast<int>(count), get_data_type(*value),
		dest, 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_recv(T* value, std::size_t count, int source)
{
	MPI_Recv(value, static_cast<int>(count), get_data_type(*value),
		source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
