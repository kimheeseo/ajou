function plot_confusionheatmap(trueClass,predictedClass)

conf_mat = confusionmat(trueClass, predictedClass);
conf_mat_per = conf_mat*100./sum(conf_mat, 2);

% Visualize model performance in heatmap
labels = {'Normal','Abnormal'};
heatmap(labels, labels, conf_mat_per,'Colormap', winter,'ColorbarVisible','off');