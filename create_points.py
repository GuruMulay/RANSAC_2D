# http://scikit-image.org/docs/dev/auto_examples/transform/plot_ransac.html
import numpy as np
from matplotlib import pyplot as plt
from skimage.measure import LineModelND, ransac

np.random.seed(seed=1)

##### specify
points_file_name = "points2"
threshold = 10

# generate coordinates of line
x = np.arange(-50, 50)
y = 0.5 * x + 20
data = np.column_stack([x, y])

# add gaussian noise to coordinates
noise = np.random.normal(size=data.shape)
data += 0.5 * noise
data[::2] += 5 * noise[::2]
# data[::4] += 10 * noise[::4]
# print("data shape", data.shape)

# add faulty data
faulty = np.array(10 * [(180., -100)])
faulty += 10 * np.random.normal(size=faulty.shape)
data[:faulty.shape[0]] = faulty
# print("data shape", data.shape)

# fit line using all data
model = LineModelND()
model.estimate(data)

# robustly fit line only using inlier data with RANSAC algorithm
model_robust, inliers = ransac(data, LineModelND, min_samples=2, residual_threshold=threshold, max_trials=20)
outliers = inliers == False
# print("inliers", inliers)
# print("outliers", outliers, np.count_nonzero(outliers))

# generate coordinates of estimated models
line_x = np.arange(-250, 250)
line_y = model.predict_y(line_x)
line_y_robust = model_robust.predict_y(line_x)

fig, ax = plt.subplots()
ax.plot(data[inliers, 0], data[inliers, 1], '.b', alpha=0.6, label='Inlier data')
ax.plot(data[outliers, 0], data[outliers, 1], '.r', alpha=0.6, label='Outlier data')
ax.plot(line_x, line_y, '-k', label='Line model from all data')
ax.plot(line_x, line_y_robust, '-b', label='Robust line model')
ax.legend(loc='lower left')
fig.savefig("./" + points_file_name + ".png")
plt.show()

data_out = np.column_stack([data, inliers])
# print("data_out:", data_out)
np.savetxt("points2_with_ground_truth.txt", data_out, delimiter=",")
np.savetxt("points2.txt", data, delimiter=",")

print("=======================================================================")
print("outlier ratio:", np.count_nonzero(outliers)/len(outliers))
print("threshold:", threshold)
print("=======================================================================")
