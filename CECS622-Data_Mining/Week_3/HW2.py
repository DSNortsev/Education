from sklearn.preprocessing import minmax_scale, StandardScaler
import numpy

data = [-5.0, 23.0, 17.6, 7.23, 1.11]
print(data)



# Min – Max  Normalization
data_norm1 = minmax_scale(data, feature_range=(0, 1), axis=0)
print(data_norm1)

data_norm2 = minmax_scale(data, feature_range=(-1, 1), axis=0)
print(data_norm2)

# Standard  Deviation  Normalization.

mean = numpy.mean(data)
std = numpy.std(data)
print(f'Mean: {mean}')
print(f'Standard Deviation : {std}')
data_norm3 = [value - mean / std for value in data]
print(data_norm3)


