from sklearn import datasets
from sklearn import svm
import matplotlib.pyplot as plt

def visualize_sepal_data():
    
    di = datasets.load_iris()
    x = di.data[:, :2] #only first two features
    #sepal length and sepal width
    y = di.target
    #make a scatter plot against just the features from all
    #featre column of 0 and 1
    plt.scatter(x[:,0], x[:,1], c=y, cmap=plt.cm.coolwarm)
    plt.xlabel('sepal Length')
    plt.ylabel('sepal Width')
    plt.title('sepal Width & length')
    plt.show()

def visualize_petal_data():
    di = datasets.load_iris()
    x = di.data[:, 2:] #get only the last 2 columsn /features
    y = di.target # these are the class tags/labels/0 setosa/1 virg/ 2 versi
    plt.scatter(x[:,0], x[:,1], c=y, cmap=plt.cm.coolwarm)
    plt.xlabel('petal Length')
    plt.ylabel('petal Width')
    plt.title('petal Width & Length')
    plt.show()

def visualize_class_data():
    di = datasets.load_iris()
    x = di.data[:, :2]
    y = di.target

    c = 1.0 #SVM regularization parameter

    # SVC with linear kernel
    svc = svm.SVC(kernel='linear', C=c).fit(x,y)
    #linear SVC (linear kernel)
    lin_svc = svm.LinearSVC(C=c).fit(x,y)
    rbf_svc = svm.SVC(kernel='rbf', gamma=0.7, C=c).fit(x,y)

    #svc with polynomial degree 3 kernel
    poly_svc = svm.SVC(kernel='poly', degree=3, C=c).fit(x,y)
    
#visualize_sepal_data()
#visualize_petal_data()

visualize_class_data()
