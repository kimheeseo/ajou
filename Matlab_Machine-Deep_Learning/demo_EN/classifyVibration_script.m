% CLASSIFYVIBRATION_SCRIPT   Generate MEX-function classifyVibration_mex from
%  classifyVibration.
% 
% Script generated from project 'classifyVibration.prj' on 10-Oct-2020.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.MexCodeConfig'.
cfg = coder.config('mex');
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;

%% Define argument types for entry-point 'classifyVibration'.
ARGS = cell(1,1);
ARGS{1} = cell(1,1);
ARGS{1}{1} = coder.typeof(0,[1 13]);

%% Invoke MATLAB Coder.
codegen -config cfg classifyVibration -args ARGS{1}

