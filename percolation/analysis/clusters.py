import numpy as np

# % Single value % #
def cluster_densities(count, L):
    return count/(L*L)


def percolating_cluster_mass(size, percolated):
    idx_percolated = np.where(percolated > 0)[0]
    if idx_percolated.size == 0:
        return 0
    return np.max(size[idx_percolated])


def percolating_cluster_density(size, percolated, L):
    return percolating_cluster_mass(size, percolated)/(L*L)


def percolating_cluster_intensity(size, percolated, L):
    return percolating_cluster_mass(size, percolated)/(L*L)


# % Multiple values (list) % #
def cluster_densities_list(count, L):
    data = [cluster_densities(count[i], L[i]) for i in range(L.size)]
    return data


def percolating_cluster_mass_list(size, percolated):
    data = [percolating_cluster_mass(size[i], percolated[i]) for i in range(len(size))]
    return np.array(data)


def percolating_cluster_density_list(size, percolated, L):
    return percolating_cluster_mass_list(size, percolated)/(L*L)


def percolating_cluster_intensity_list(size, percolated, L):
    return percolating_cluster_mass_list(size, percolated)/(L*L)
