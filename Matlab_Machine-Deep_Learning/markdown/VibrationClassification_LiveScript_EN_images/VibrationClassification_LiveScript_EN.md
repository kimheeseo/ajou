# Classify normal and abnormal vibration data


This script demonstrates the complete workflow for developing an embedded machine learning application,including acquiring the data, extracting features, exploring various algorithms, tuning to get a model with good performance, and  deploying the model in a prototype application. Specifically, we develop a classifier of vibration signal from a wind turbine into 'Normal' and 'Abnormal', which could be used in predictive maintenance system to monitor the engineering assets.




THIS SCRIPT IS INTENDED TO BE STEPPED THROUGH SECTION BY SECTION, because of the interactive Signal Analyzer and Classification Learner apps that it calls. If you try to run the complete script, errors are likely to occur.




The figure below shows the high-level architecture and a screenshot from the prototype.




![image_0.png](VibrationClassification_LiveScript_EN_images/image_0.png)




Copyright 2019 The MathWorks, Inc.




The demo is structured according to the four phases of the typical machine learning workflow:



   1.  Access and Explore Data 
   1.  Preproess Data 
   1.  Develop Predictive Models 
   1.  Integrate Models with Systems 



The figure below shows which additional MATLAB toolboxes we will leverage in the various phases of the workflow.




![image_1.png](VibrationClassification_LiveScript_EN_images/image_1.png)


# Access and Explore Data 

Load the preprocessed data saved in  `sampleData.mat. See` `dataPreparation.mlx for the details.`



```matlab:Code
load('sampleData.mat');
```



Take two sample vibration signal for a quick comparison.



```matlab:Code
vib1 = sampleData.vibration{1}.Variables; % Normal
vib2 = sampleData.vibration{25}.Variables; % Abnormal
```


# What do the signals look like in the frequency domain?


To explore what we might use to distinguish these signals with a classifier, let's look at their frequency content. To this end, you can use MATLAB's [Signal Analyzer](https://www.mathworks.com/help/signal/ug/getting-started-with-signal-analyzer-app.html) app to inspect and compare the power spectrum of the two signals.



```matlab:Code
signalAnalyzer(vib1,vib2)
```



Once the app has loaded, display the signals in two separate panels (use the Grid button on the left upper corner), and then generate the Spectrum underneath the waveform (by clicking the corresponding button).




![image_4.png](VibrationClassification_LiveScript_EN_images/image_4.png)


# Extract features from raw vibration signals


Next we need to extract features from the raw recordings. We use Diagnostic Feature Designer available in Predictive Maintenance Toolbox to process and extract features from the raw vibration signal. The following section extracts features for each recording, and splits each recording into windows consisting of 0.2 seconds of vibration signal.




To avoid this step, you can simply load the extracted features from `FeatureTable.mat` that we included with the demo.




![image_6.png](VibrationClassification_LiveScript_EN_images/image_6.png)



```matlab:Code
load('FeatureTable.mat');
disp(FeatureTable1(1:5,:))
```

# Train, compare and select classifier 


Having an initial set of features, we can proceed to the next phase of the machine learning workflow, the training of various predictive models. You can use the [Classification Learner App](https://www.mathworks.com/help/stats/classificationlearner-app.html) to interactively train, compare and select classifiers.



```matlab:Code
classificationLearner
```



Select the `FeatureTable1` variable from the workspace as your data, and either hold out 30% as model "validation" data, or (to preserve more data for training) choose cross validation. 




Then train a bunch of different classifiers, including linear regression, SVM, and decision trees. Note which ones deliver higher accuracy on the held out validation data. Also explore the confusion matrices and conceptualize what misclassifying a normal versus an abnormal vibration means in practice.




To improve model performance, the following sections will apply additional optimization steps. Generate `trainClassifier.m` from the app that reproduces the trained classifier of your choice.


# Split data into training and testing sets. 


These optimization steps need to be performed programmatically. Therefore, we first need to split the data like we did within the Classification Learner app, and to match our work in the app, holding out 30% of the (training) data for testing. Use [cvpartition](https://www.mathworks.com/help/stats/cvpartition.html) to split data into training and testing sets. Use [tabulate](https://www.mathworks.com/help/stats/tabulate.html) to see number of observations for each class.



```matlab:Code
rng(1)
% Use 30% of data for training and remaining for testing
split_data = cvpartition(FeatureTable1.faultcode, 'Holdout', 0.3);
% Create a training set
trainingData = FeatureTable1(split_data.training, :);
% Create a test set (won't be used until much later)
testingData = FeatureTable1(split_data.test, :);
tabulate(trainingData.faultcode)
```



Let's reproduce the confusion matrix of the classifier of your choice from the Classification Learner App. Note that `trainedClassifier `is the auto generate function from the app.



```matlab:Code
trained_model = trainClassifier(trainingData);
predictedCode = trained_model.predictFcn(testingData);
plot_confusionheatmap(testingData.faultcode, predictedCode)
```



A fairly high number of abnormal vibrations are misclassified as normal


# Optimization 1: Train the classifier with misclassification cost


To bias the classifier towards fewer misclassifications of abnormal vibrations, we use a cost function that assigns higher misclassification cost, say double, to the 'Abnormal' class. We continue with the k-nearest neighbor. Note that misclassification of abnormal vibration decreases and that of normal vibration increases.



```matlab:Code(Display)
classificationKNN = fitcknn(...
    predictors, ...
    response, ...
    'Distance', 'Euclidean', ...
    'Exponent', [], ...
    'NumNeighbors', 10, ...
    'Cost',[0,2;1,0], ...  % < add a line on the trainedClassifier.m
    'DistanceWeight', 'Equal', ...
    'Standardize', true, ...
    'ClassNames', [0; 1]);
```



Retrain the model and check the confusion matrix.



```matlab:Code
trained_model = trainClassifier(trainingData);

predictedCode = trained_model.predictFcn(testingData);
plot_confusionheatmap(testingData.faultcode, predictedCode)
```



![image_10.png](VibrationClassification_LiveScript_EN_images/image_10.png)


# Optimization 2: Hyperparameter tuning


We perform hyperparameter tuning by using [Bayesian Optimization](https://www.mathworks.com/help/stats/bayesian-optimization-workflow.html) to find optimal values for model parameters. 



```matlab:Code(Display)
classificationKNN = fitcknn(...
    predictors, ...
    response, ...
    'Distance', 'Euclidean', ...
    'Exponent', [], ...
    'NumNeighbors', 10, ...
    'Cost',[0,2;1,0], ... % the line added in the above step (Optimization 1)
    'OptimizeHyperparameters', 'auto', ... % < add another line on the trainedClassifier.m
    'DistanceWeight', 'Equal', ...
    'Standardize', true, ...
    'ClassNames', [0; 1]);
```



Retrain the model and check the confusion matrix.



```matlab:Code
trained_model = trainClassifier(trainingData);
predictedCode = trained_model.predictFcn(testingData);
plot_confusionheatmap(testingData.faultcode, predictedCode)
```



Comparing with the original model, you can see that misclassification of abnormal and normal vibration are both descreased.


# [Optional] Perform feature selection using Neighborhood Component Analysis


In this optional section we explore training a more compact model that uses only a subset of the 15 features, namely the features that have the majority of the predictive power. [Neighborhood Component Analysis](https://www.mathworks.com/help/stats/neighborhood-component-analysis.html) (NCA) is an automated approach for  selecting a small subset of features that carry information most relevant to the classification task while minimizing redudancy among selected features. 



```matlab:Code
flagNCA = false;
if ~flagNCA 
    selected_feature_indx = 3:15;
    
else % Perform feature selection with neighborhood component analysis
    X = table2array(trainingData(:,3:15));
    Y = table2array(trainingData(:,16));
    mdl = fscnca(X, Y, 'Lambda', 1e-4, 'Verbose', 0);
    
    % Select features with weight above 0.1
    selected_feature_indx = find(mdl.FeatureWeights > 0.1) + 2;
    
    % Plot feature weights
    stem(mdl.FeatureWeights,'bo');
    save('SelectedFeatures.mat','selected_feature_indx');
    predName = trainingData.Properties.VariableNames(selected_feature_indx)
```



To actually get a more compact model for deployment, we retrain the model using only selected features. 




Retrain the model and check the confusion matrix.



```matlab:Code
    trained_model = trainClassifier_selected(trainingData,predName);
    predictedCode = trained_model.predictFcn(testingData);
    plot_confusionheatmap(testingData.faultcode, predictedCode)
end
```

# Code Generation


Generate C code that takes the extracted features as input and produces vibration classification label as output. In practice, putting the feature extraction part into the generated C code is desiable for many cases but we leave it out for the sake of simplicity.




Check the name of the trained model. 



```matlab:Code
    trained_model
```



You may need to rewrite the model name (`ClassificationKNN` below) to the name of the model.



```matlab:Code
    % Save trained model as a compact model for code generation
    saveCompactModel(trained_model.ClassificationKNN,'ClassificationModel')
```



We use MATLAB Coder app available in MATLAB Coder. The app helps go through the required setting to generate C code from MATLAB function, **`classifyVibration.m`**




![image_13.png](VibrationClassification_LiveScript_EN_images/image_13.png)


# Validate final model


Process the validation set by calling the mex version of the function **`classifyVibration.m`**



```matlab:Code
    idx = 36;
    predictedCode = classifyVibration_mex(testingData{idx,selected_feature_indx});
    disp("Prediction： " + string(predictedCode) + " / Ground Truth: " + string(testingData.faultcode(idx)))
```



*Copyright 2019 The MathWorks, Inc.*


