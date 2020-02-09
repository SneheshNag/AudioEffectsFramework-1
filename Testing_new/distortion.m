function [x]=distortion(a,x)
%[Y] = distortion(audio_test, A, X) Guitar Distortion
%
%   Distortion creates a distortion effect like that of
%   an overdriven guitar amplifier. This is a Matlab 
%   implementation of an algorithm that was found on 
%   www.musicdsp.org.
%   audio_test = filtered audio from C++ code
%   A = The amount of distortion.  A
%       should be chosen so that -1<A<1.
%   X = Input.  Should be a column vector 
%       between -1 and 1.
%
%coded by: Steve McGovern, date: 09.29.04
%URL: http://www.steve-m.us

k = 2*a/(1-a);
x = (1+k)*(x)./(1+k*abs(x));
