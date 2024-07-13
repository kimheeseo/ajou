% Dataset from WindTurbine shipping demo
dirname = '../../WindTurbineData';

% Add faultcode to the MAT file (will be used as a condition variable)
s = dir([dirname, '\*201303*']);
faultcode = false; % for data measured in March
for ii=1:length(s)
   filename = s(ii).name;
   save(fullfile(dirname,filename),'faultcode','-append');
end

s = dir([dirname, '\*201304*']);
faultcode = true; % for data measured in April
for ii=1:length(s)
   filename = s(ii).name;
   save(fullfile(dirname,filename),'faultcode','-append');
end

% Create a fileEnsembleDatastore of the wind turbine data
hsbearing = fileEnsembleDatastore(fullfile(dirname), '.mat');
hsbearing.DataVariables = "vibration";
hsbearing.IndependentVariables = "Date";
hsbearing.ConditionVariables = "faultcode";
hsbearing.SelectedVariables = ["Date", "vibration", "faultcode"];
hsbearing.ReadFcn = @helperReadData;
hsbearing.WriteToMemberFcn = @helperWriteToHSBearing;