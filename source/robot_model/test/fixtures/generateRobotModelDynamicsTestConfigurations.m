function generateRobotModelDynamicsTestConfigurations(urdf, nConfigurations, seed)
% Generate configurations and expected results for a robot model
%
%   generateRobotModelDynamicsTestConfigurations expects a file 
%   `panda_arm.urdf` in the same folder and generates 3 random
%   configurations of joint position, velocity and acceleration. It
%   calculates the joint-space gravity, coriolis and inertia torques for
%   each configuration and prints out a C++ formatted result to be used
%   in test fixtures.
%
%   generateRobotModelDynamicsTestConfigurations(urdf) takes a filepath to
%   a urdf robot model to load.
%
%   generateRobotModelDynamicsTestConfigurations(urdf, nConfigurations)
%   generates number of random configurations (default 3).
%
%   generateRobotModelDynamicsTestConfigurations(..., seed) allows
%   setting the seed for the random number generator. The input is either
%   'default' for repeatable behaviour or 'shuffle' for a time-based seed.
%
%   Requires Robotics System Toolbox

arguments
    urdf string = 'panda_arm.urdf';
    nConfigurations (1,1) double = 3;
    seed (1,:) char {mustBeMember(seed,{'default','shuffle'})} = 'default'
end

% initialise the random number generator
rng(seed)

% load the robot model
robot = importrobot(urdf);
robot.DataFormat = 'row';
robot.Gravity = [0 0 -9.81];

% helper function to format numeric array [a, b, c] into '{a, b, c}'
num2stdvec = @(A) (['{', strjoin(compose('%f', A), ', ') '}']);

% code generation (declarations)
fprintf('std::vector<state_representation::JointState> test_configs;\n');
fprintf('std::vector<std::vector<double>> test_gravity_expects;\n');
fprintf('std::vector<std::vector<double>> test_coriolis_expects;\n');
fprintf('std::vector<std::vector<double>> test_inertia_expects;\n');

% generate the configurations
for conf = 1:nConfigurations
    % configurations
    q = robot.randomConfiguration;
    v = rand(size(q))*2 - 1;
    a = rand(size(q))*2 - 1;
    
    % expected results
    G = robot.gravityTorque(q);
    C = robot.velocityProduct(q, v);
    M = a * robot.massMatrix(q);
    
    % code generation (definitions)
    fprintf('\n// Random test configuration %i:\n', conf);
    fprintf(['state_representation::JointState config%i', ...
        '(franka->get_robot_name(), %i);\n'], conf, numel(q));
    fprintf('config%i.set_positions(%s);\n', conf, num2stdvec(q));
    fprintf('config%i.set_velocities(%s);\n', conf, num2stdvec(v));
    fprintf('config%i.set_accelerations(%s);\n', conf, num2stdvec(a));
    fprintf('test_configs.push_back(config%i);\n', conf);
    
    fprintf('\n// Expected results for configuration %i:\n', conf);
    fprintf('test_gravity_expects.push_back(%s);\n', num2stdvec(G));
    fprintf('test_coriolis_expects.push_back(%s);\n', num2stdvec(C));
    fprintf('test_inertia_expects.push_back(%s);\n', num2stdvec(M));
end
