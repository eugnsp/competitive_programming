#pragma once
#include <mpi.h>

#include <cstddef>
#include <type_traits>
#include <vector>

template<typename T>
struct Data_type;

template<>
struct Data_type<unsigned char>
{
	static constexpr auto value = MPI_UNSIGNED_CHAR;
};

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

template<>
struct Data_type<double>
{
	static constexpr auto value = MPI_DOUBLE;
};

template<typename T>
void mpi_bcast(T& value)
{
	using S = std::remove_const_t<T>;
	MPI_Bcast(const_cast<S*>(&value), 1, Data_type<S>::value, 0, MPI_COMM_WORLD);
}

template<typename... Ts>
void mpi_bcast(Ts&... values)
{
	(mpi_bcast(values), ...);
}

template<typename T>
void mpi_send(const T* buff, std::size_t count, unsigned int dest,
	MPI_Datatype datatype = Data_type<T>::value)
{
	MPI_Send(buff, static_cast<int>(count), datatype, static_cast<int>(dest), 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_recv(
	T* buff, std::size_t count, unsigned int source, MPI_Datatype datatype = Data_type<T>::value)
{
	MPI_Recv(buff, static_cast<int>(count), datatype, static_cast<int>(source), 0, MPI_COMM_WORLD,
		MPI_STATUS_IGNORE);
}

template<typename T>
void mpi_scatterv_send(
	const T* buff, const std::vector<int>& sizes, const std::vector<int>& offsets)
{
	MPI_Scatterv(const_cast<T*>(buff), sizes.data(), offsets.data(), Data_type<T>::value,
		MPI_IN_PLACE, 0, 0, 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_scatterv_recv(T* buff, std::size_t size)
{
	MPI_Scatterv(nullptr, nullptr, nullptr, 0, buff, static_cast<int>(size), Data_type<T>::value, 0,
		MPI_COMM_WORLD);
}

template<typename T>
void mpi_gatherv_send(const T* buff, std::size_t size)
{
	MPI_Gatherv(const_cast<T*>(buff), static_cast<int>(size), Data_type<T>::value, nullptr, nullptr,
		nullptr, 0, 0, MPI_COMM_WORLD);
}

template<typename T>
void mpi_gatherv_recv(T* buff, const std::vector<int>& sizes, const std::vector<int>& offsets)
{
	MPI_Gatherv(MPI_IN_PLACE, 0, 0, buff, sizes.data(), offsets.data(), Data_type<T>::value, 0,
		MPI_COMM_WORLD);
}

template<typename T>
MPI_Datatype mpi_create_padded_block_type(std::size_t size, std::size_t total_size)
{
	MPI_Datatype tmp_type;
	MPI_Datatype type;

	MPI_Type_contiguous(static_cast<int>(size), Data_type<T>::value, &tmp_type);
	MPI_Type_create_resized(tmp_type, 0, static_cast<MPI_Aint>(total_size), &type);
	MPI_Type_commit(&type);

	return type;
}

void mpi_type_free(MPI_Datatype& datatype)
{
	MPI_Type_free(&datatype);
}
