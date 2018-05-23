# KNNC-3fold-naiveBayes
Aim:

Task_1: Find k to be used in k-nearest neighbor classifier (k-NNC) using a 3-fold cross validation. With k value error rate has to be calculated.

Task_2:  Employing Naive Bayes Classifier on the given test data and printing the accuracy.

Procedure:

k-NNC:

•	K-NNC classifies data sets based on their similarity with neighbors.

•	It choses its class based on the neighbor’s class which are of nearest proximity.

•	Proximity Metric Used: Euclidean Distance (which is equal to straight line distance.)

•	The value of k is found out using 3-fold cross validation technique.

•	The error rates are calculated on the validation set for a range of k values.

•	Then argmin of the mean of all the error rates (argmin{e1, e2, ….,ej, …, em} ) is considered as the k value.

•	Using the obtained k value, the test data is tested, and accuracy is calculated based on the correct classifications.

Naive Bayes Classifier:

•	Naive Bayes Classifier is based on Bayes Theorem.

•	It is assumed that the features are independent of each other.

•	The probability of occurrence of a feature value is its frequency ratio.

•	The minimum error rate for each feature is calculated.

•	Then maximum discrimination is the max posterior which is also calculated.

•	Logarithm is applied based multiplication of small numbers becomes very small often result is zero.

•	The class with maximum probability is picked out.

Results:

For k-NNC:

K value: 1

Accuracy: 90.009001 %



For Naive Bayes Classifier:

Accuracy: 81.698170%

Conclusion: k-NNC is often not seen as a related classifier to Bayes classifier. This is because, distributions are not explicitly calculated. The time and space complexity of kNNC are both equal to O(n) whereas the time complexity of Naive Bayes Classifier is O(1).

