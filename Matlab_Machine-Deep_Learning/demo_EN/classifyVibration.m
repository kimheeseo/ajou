function label = classifyVibration(features) %#codegen
%Label new observations using trained SVM model Mdl. The function takes 
%sound signal and sampling frequency as input and produces a classification
%of 'Normal' or 'Abnormal'
%Copyright (c) 2016-2019, MathWorks, Inc. 

% Load saved model 
Mdl = loadCompactModel('ClassificationModel');

% Predict classification for all windows
label = predict(Mdl,features);

% Predict abnormal if even one window sounds abnormal

end