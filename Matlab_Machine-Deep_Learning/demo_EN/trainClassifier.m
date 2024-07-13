function [trainedClassifier, validationAccuracy] = trainClassifier(trainingData)
% [trainedClassifier, validationAccuracy] = trainClassifier(trainingData)
% 훈련된 분류기와 그 정확도을(를) 반환합니다. 이 코드는 분류 학습기 앱에서 훈련된 분류
% 모델을 다시 만듭니다. 생성된 코드를 사용하여 동일한 모델을 새 데이터로 훈련시키는 것을
% 자동화하거나, 모델을 프로그래밍 방식으로 훈련시키는 방법을 익힐 수 있습니다.
%
%  입력값:
%      trainingData: 앱으로 가져온 것과 동일한 예측 변수와 응답 변수 열을 포함하는 테
%       이블입니다.
%
%  출력값:
%      trainedClassifier: 훈련된 분류기가 포함된 구조체입니다. 이 구조체에는 훈련된
%       분류기에 대한 정보가 포함된 다양한 필드가 들어 있습니다.
%
%      trainedClassifier.predictFcn: 새 데이터를 사용하여 예측하기 위한 함수입니
%       다.
%
%      validationAccuracy: 정확도(%)를 포함하는 double형입니다. 이 전반적인 정확도
%       점수는 앱의 내역 목록에 각 모델별로 표시됩니다.
%
% 새 데이터로 모델을 훈련시키려면 이 코드를 사용하십시오. 분류기를 다시 훈련시키려면 명령
% 줄에서 원래 데이터나 새 데이터를 입력 인수 trainingData(으)로 사용하여 함수를 호출하
% 십시오.
%
% 예를 들어, 원래 데이터 세트 T(으)로 훈련된 분류기를 다시 훈련시키려면 다음을 입력하십
% 시오.
%   [trainedClassifier, validationAccuracy] = trainClassifier(T)
%
% 새 데이터 T2에서 반환된 'trainedClassifier'을(를) 사용하여 예측하려면 다음을 사용
% 하십시오.
%   yfit = trainedClassifier.predictFcn(T2)
%
% T2은(는) 적어도 훈련 중에 사용된 것과 동일한 예측 변수 열을 포함하는 테이블이어야 합니
% 다. 세부 정보를 보려면 다음을 입력하십시오.
%   trainedClassifier.HowToPredict

% MATLAB에서 2021-04-22 15:17:50에 자동 생성됨


% 예측 변수와 응답 변수 추출
% 이 코드는 모델을 훈련시키기에 적합한 형태로 데이터를
% 처리합니다.
inputTable = trainingData;
predictorNames = {'FRM_1_vibration_stats_Var1_ClearanceFactor', 'FRM_1_vibration_stats_Var1_CrestFactor', 'FRM_1_vibration_stats_Var1_ImpulseFactor', 'FRM_1_vibration_stats_Var1_Kurtosis', 'FRM_1_vibration_stats_Var1_Mean', 'FRM_1_vibration_stats_Var1_PeakValue', 'FRM_1_vibration_stats_Var1_RMS', 'FRM_1_vibration_stats_Var1_SINAD', 'FRM_1_vibration_stats_Var1_SNR', 'FRM_1_vibration_stats_Var1_ShapeFactor', 'FRM_1_vibration_stats_Var1_Skewness', 'FRM_1_vibration_stats_Var1_Std', 'FRM_1_vibration_stats_Var1_THD'};
predictors = inputTable(:, predictorNames);
response = inputTable.faultcode;
isCategoricalPredictor = [false, false, false, false, false, false, false, false, false, false, false, false, false];

% 분류기 훈련
% 이 코드는 모든 분류기 옵션을 지정하고 분류기를 훈련시킵니다.
classificationKNN = fitcknn(...
    predictors, ...
    response, ...
    'Distance', 'Minkowski', ...
    'Exponent', 3, ...
    'NumNeighbors', 10, ...
    'Cost',[0,2;1,0], ... % the line added in the above step (Optimization 1)
    'OptimizeHyperparameters', 'auto', ... % < add another line on the trainedClassifier.m
    'DistanceWeight', 'Equal', ...
    'Standardize', true, ...
    'ClassNames', {'abnormal'; 'normal'});

% 예측 함수를 사용하여 결과 구조체 생성
predictorExtractionFcn = @(t) t(:, predictorNames);
knnPredictFcn = @(x) predict(classificationKNN, x);
trainedClassifier.predictFcn = @(x) knnPredictFcn(predictorExtractionFcn(x));

% 추가적인 필드를 결과 구조체에 추가
trainedClassifier.RequiredVariables = {'FRM_1_vibration_stats_Var1_ClearanceFactor', 'FRM_1_vibration_stats_Var1_CrestFactor', 'FRM_1_vibration_stats_Var1_ImpulseFactor', 'FRM_1_vibration_stats_Var1_Kurtosis', 'FRM_1_vibration_stats_Var1_Mean', 'FRM_1_vibration_stats_Var1_PeakValue', 'FRM_1_vibration_stats_Var1_RMS', 'FRM_1_vibration_stats_Var1_SINAD', 'FRM_1_vibration_stats_Var1_SNR', 'FRM_1_vibration_stats_Var1_ShapeFactor', 'FRM_1_vibration_stats_Var1_Skewness', 'FRM_1_vibration_stats_Var1_Std', 'FRM_1_vibration_stats_Var1_THD'};
trainedClassifier.ClassificationKNN = classificationKNN;
trainedClassifier.About = '이 구조체는 분류 학습기 R2020b에서 내보낸 훈련된 모델입니다.';
trainedClassifier.HowToPredict = sprintf('새 테이블 T를 사용하여 예측하려면 다음을 사용하십시오. \n yfit = c.predictFcn(T) \n여기서 ''c''를 이 구조체를 나타내는 변수의 이름(예: ''trainedModel'')으로 바꾸십시오. \n \n테이블 T는 다음에서 반환된 변수를 포함해야 합니다. \n c.RequiredVariables \n변수 형식(예: 행렬/벡터, 데이터형)은 원래 훈련 데이터와 일치해야 합니다. \n추가 변수는 무시됩니다. \n \n자세한 내용은 <a href="matlab:helpview(fullfile(docroot, ''stats'', ''stats.map''), ''appclassification_exportmodeltoworkspace'')">How to predict using an exported model</a>을(를) 참조하십시오.');

% 예측 변수와 응답 변수 추출
% 이 코드는 모델을 훈련시키기에 적합한 형태로 데이터를
% 처리합니다.
inputTable = trainingData;
predictorNames = {'FRM_1_vibration_stats_Var1_ClearanceFactor', 'FRM_1_vibration_stats_Var1_CrestFactor', 'FRM_1_vibration_stats_Var1_ImpulseFactor', 'FRM_1_vibration_stats_Var1_Kurtosis', 'FRM_1_vibration_stats_Var1_Mean', 'FRM_1_vibration_stats_Var1_PeakValue', 'FRM_1_vibration_stats_Var1_RMS', 'FRM_1_vibration_stats_Var1_SINAD', 'FRM_1_vibration_stats_Var1_SNR', 'FRM_1_vibration_stats_Var1_ShapeFactor', 'FRM_1_vibration_stats_Var1_Skewness', 'FRM_1_vibration_stats_Var1_Std', 'FRM_1_vibration_stats_Var1_THD'};
predictors = inputTable(:, predictorNames);
response = inputTable.faultcode;
isCategoricalPredictor = [false, false, false, false, false, false, false, false, false, false, false, false, false];

% 교차 검증 수행
partitionedModel = crossval(trainedClassifier.ClassificationKNN, 'KFold', 5);

% 검증 예측값 계산
[validationPredictions, validationScores] = kfoldPredict(partitionedModel);

% 검증 정확도 계산
validationAccuracy = 1 - kfoldLoss(partitionedModel, 'LossFun', 'ClassifError');
