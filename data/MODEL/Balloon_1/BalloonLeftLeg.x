xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 123;
 -1.53212;-0.65223;1.05057;,
 1.47151;0.32382;2.82351;,
 1.04242;-0.64752;1.07415;,
 2.75881;0.03147;0.13581;,
 -2.16398;0.32382;2.79051;,
 -3.39467;0.03147;-0.24141;,
 3.38593;-15.22722;-4.90014;,
 2.26840;-10.72410;-6.24870;,
 1.96189;-9.23406;-4.13625;,
 3.31990;-15.22722;-1.53342;,
 -2.46575;-16.00521;4.63890;,
 -3.36164;-16.00521;-1.25991;,
 3.15961;-16.00521;-1.20333;,
 1.68841;-16.00521;4.67190;,
 -3.55970;-15.22722;-1.59471;,
 -3.32393;-16.00521;-4.91898;,
 3.38593;-16.00521;-4.85769;,
 3.31990;-15.22722;-1.53342;,
 -2.39501;-6.59820;4.29939;,
 -3.36164;-7.07919;0.65448;,
 -3.64457;-10.46007;0.65448;,
 -2.23940;-7.18764;-3.02343;,
 -2.21111;-9.23406;-4.17396;,
 1.47625;-7.18764;-2.99043;,
 3.02758;-7.07919;0.90912;,
 3.50851;-10.46007;0.92796;,
 1.56112;-6.59820;4.33242;,
 -2.16869;-10.72410;-6.28641;,
 2.70691;-12.12927;-9.52584;,
 3.15961;-16.00521;-1.20333;,
 3.31990;-15.22722;-1.53342;,
 3.40480;-15.22722;0.87609;,
 3.38593;-16.00521;-4.85769;,
 3.38593;-15.22722;-4.90014;,
 -3.36164;-7.07919;0.65448;,
 -4.05479;-6.47094;0.77709;,
 -2.53649;-6.51807;-3.48081;,
 -2.23940;-7.18764;-3.02343;,
 -2.39501;-6.59820;4.29939;,
 -2.54117;-5.93334;4.77093;,
 -4.05479;-6.47094;0.77709;,
 -3.36164;-7.07919;0.65448;,
 -3.32393;-16.00521;-4.91898;,
 -3.32393;-15.22722;-4.95672;,
 -3.53141;-15.22722;-9.21462;,
 -3.53141;-16.00521;-9.23349;,
 -3.32393;-15.22722;-4.95672;,
 -2.55536;-12.12927;-9.57297;,
 -3.53141;-15.22722;-9.21462;,
 -2.46575;-16.00521;4.63890;,
 -2.75810;-15.22722;4.66248;,
 -3.83318;-15.22722;0.81480;,
 -1.34822;-13.48254;-14.59005;,
 -1.90934;-15.22722;-14.13738;,
 0.39172;-15.22722;-15.25962;,
 1.80631;-13.48254;-14.56176;,
 -3.53141;-16.00521;-9.23349;,
 -2.09795;-16.00521;-14.13267;,
 2.54662;-16.00521;-14.09022;,
 4.04134;-16.00521;-9.16746;,
 0.39172;-16.00521;-15.27375;,
 -3.36164;-16.00521;-1.25991;,
 -1.90934;-15.22722;-14.13738;,
 -2.09795;-16.00521;-14.13267;,
 0.39172;-15.22722;-15.25962;,
 0.39172;-16.00521;-15.27375;,
 3.40480;-15.22722;0.87609;,
 1.96663;-10.64865;4.86525;,
 1.96189;-15.22722;4.70493;,
 -3.55970;-15.22722;-1.59471;,
 -2.73923;-10.64865;4.82280;,
 -0.41930;-6.59820;4.54932;,
 -0.39104;-10.64865;5.38392;,
 3.02758;-7.07919;0.90912;,
 3.57454;-6.47094;1.09773;,
 1.76386;-5.93334;4.80864;,
 1.56112;-6.59820;4.33242;,
 -2.75810;-15.22722;4.66248;,
 -0.40517;-15.22722;5.21889;,
 -3.55970;-15.22722;-1.59471;,
 -3.83318;-15.22722;0.81480;,
 1.68841;-16.00521;4.67190;,
 2.35801;-15.22722;-14.09967;,
 4.04134;-15.22722;-9.14859;,
 1.96189;-15.22722;4.70493;,
 4.04134;-16.00521;-9.16746;,
 4.04134;-15.22722;-9.14859;,
 -0.41930;-6.59820;4.54932;,
 2.54662;-16.00521;-14.09022;,
 2.35801;-15.22722;-14.09967;,
 -0.40517;-15.22722;5.21889;,
 1.73086;-6.51807;-3.44781;,
 1.47625;-7.18764;-2.99043;,
 -3.78131;-0.05811;-0.13767;,
 -3.39467;0.03147;-0.24141;,
 -2.10740;-0.06753;-3.65058;,
 -2.33372;-0.15714;-4.00893;,
 -2.16869;0.29085;3.46008;,
 -2.16398;0.32382;2.79051;,
 -3.39467;0.03147;-0.24141;,
 -3.78131;-0.05811;-0.13767;,
 1.52809;-0.06753;-3.61758;,
 1.75915;-0.15714;-3.97593;,
 2.75881;0.03147;0.13581;,
 3.14545;-0.05811;0.31026;,
 1.47151;0.32382;2.82351;,
 1.69315;0.20124;3.46008;,
 -0.40517;-15.22722;5.21889;,
 -0.39104;-10.64865;5.38392;,
 -0.41930;-6.59820;4.54932;,
 3.56758;-6.44628;1.10646;,
 1.75120;-4.83573;4.56735;,
 3.57322;-6.45129;1.09533;,
 -0.26813;-3.15912;-3.74226;,
 1.73806;-4.90068;-3.58209;,
 -2.37122;-1.33353;-3.91125;,
 0.24547;-3.53013;4.28796;,
 -2.26700;-1.35177;3.80604;,
 2.03119;-5.14659;-2.64996;,
 -3.77747;-0.07623;-0.12252;,
 -3.78191;-0.07251;-0.13563;,
 -2.59883;-1.12977;-3.27165;,
 -3.78191;-0.07251;-0.13563;;
 
 134;
 3;0,1,2;,
 3;2,1,3;,
 3;0,4,1;,
 3;5,4,0;,
 3;6,7,8;,
 3;6,8,9;,
 3;10,11,12;,
 3;10,12,13;,
 3;14,15,16;,
 3;14,16,17;,
 3;17,12,11;,
 3;17,11,14;,
 3;18,19,20;,
 3;19,21,22;,
 3;8,23,24;,
 3;25,24,26;,
 3;27,7,28;,
 3;22,8,7;,
 3;29,30,31;,
 3;7,27,22;,
 3;32,33,30;,
 3;34,35,36;,
 3;34,36,37;,
 3;38,39,40;,
 3;38,40,41;,
 3;42,43,44;,
 3;42,44,45;,
 3;46,27,47;,
 3;46,47,48;,
 3;49,50,51;,
 3;48,47,52;,
 3;48,52,53;,
 3;53,52,54;,
 3;52,47,28;,
 3;52,28,55;,
 3;52,55,54;,
 3;56,57,58;,
 3;56,58,59;,
 3;57,60,58;,
 3;51,61,49;,
 3;62,63,45;,
 3;62,45,44;,
 3;64,65,63;,
 3;64,63,62;,
 3;66,25,67;,
 3;66,67,68;,
 3;69,43,42;,
 3;23,8,22;,
 3;23,22,21;,
 3;22,20,19;,
 3;20,70,18;,
 3;71,18,70;,
 3;71,70,72;,
 3;73,74,75;,
 3;73,75,76;,
 3;24,25,8;,
 3;72,70,77;,
 3;72,77,78;,
 3;51,69,61;,
 3;79,22,27;,
 3;79,27,46;,
 3;20,22,79;,
 3;20,79,80;,
 3;77,70,20;,
 3;77,20,80;,
 3;31,81,29;,
 3;54,55,82;,
 3;82,55,28;,
 3;82,28,83;,
 3;31,84,81;,
 3;83,28,7;,
 3;83,7,6;,
 3;59,16,15;,
 3;59,15,56;,
 3;85,86,33;,
 3;85,33,32;,
 3;87,76,75;,
 3;28,47,27;,
 3;26,67,25;,
 3;86,85,88;,
 3;86,88,89;,
 3;89,88,65;,
 3;89,65,64;,
 3;25,66,9;,
 3;25,9,8;,
 3;81,84,90;,
 3;37,36,91;,
 3;37,91,92;,
 3;92,91,74;,
 3;92,74,73;,
 3;93,94,95;,
 3;93,95,96;,
 3;97,98,99;,
 3;97,99,100;,
 3;96,95,101;,
 3;96,101,102;,
 3;102,101,103;,
 3;102,103,104;,
 3;104,103,105;,
 3;104,105,106;,
 3;106,105,98;,
 3;106,98,97;,
 3;107,68,67;,
 3;107,67,108;,
 3;108,67,26;,
 3;108,26,109;,
 3;90,50,49;,
 3;49,81,90;,
 3;39,38,87;,
 3;87,75,39;,
 3;110,106,111;,
 4;110,111,75,74;,
 3;110,74,112;,
 4;110,112,104,106;,
 3;113,102,114;,
 4;113,114,91,36;,
 3;113,36,115;,
 4;113,115,96,102;,
 3;116,97,117;,
 4;116,117,39,75;,
 3;116,75,111;,
 4;116,111,106,97;,
 3;118,104,112;,
 4;118,112,74,91;,
 3;118,91,114;,
 4;118,114,102,104;,
 3;119,100,120;,
 4;119,120,40,39;,
 3;119,39,117;,
 4;119,117,97,100;,
 3;121,96,115;,
 4;121,115,36,35;,
 3;121,35,122;,
 4;121,122,93,96;;
 
 MeshMaterialList {
  8;
  134;
  4,
  4,
  4,
  4,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  5,
  5,
  5,
  5,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  5,
  5,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  5,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  5,
  5,
  5,
  5,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  3,
  3,
  3,
  3,
  3,
  3,
  5,
  5,
  4,
  5,
  0,
  4,
  4,
  5,
  5,
  4,
  4,
  5,
  5,
  4,
  4,
  5,
  5,
  4,
  0,
  5,
  5,
  4,
  4,
  5,
  5,
  4;;
  Material {
   0.065600;0.037600;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.775200;0.612000;0.489600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.084800;0.232000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.627200;0.677600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.116000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.724706;0.552157;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.285600;0.800000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.683922;0.489412;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  118;
  -0.157970;0.974501;-0.159355;,
  -0.084712;0.991845;-0.095228;,
  0.173488;0.884896;-0.432273;,
  -0.255800;0.870449;-0.420577;,
  0.009932;0.982321;-0.186940;,
  0.076321;0.977589;-0.196199;,
  0.059420;0.988102;-0.141855;,
  0.040851;0.993684;-0.104520;,
  0.988953;0.125959;0.078139;,
  0.952577;0.303173;0.026124;,
  0.958219;0.222796;-0.179382;,
  0.997966;0.019017;-0.060848;,
  -0.202148;-0.943545;0.262409;,
  -0.637332;-0.770589;-0.000688;,
  0.251798;-0.965724;0.063052;,
  0.476191;-0.784363;0.397513;,
  -0.002055;-0.973709;0.227786;,
  -0.000697;-0.997080;0.076359;,
  -0.001378;-0.988264;0.152753;,
  -0.915430;-0.271721;0.296910;,
  -0.943268;-0.317293;-0.097825;,
  -0.996748;0.066888;0.044936;,
  -0.939104;-0.198214;-0.280704;,
  -0.963158;0.125055;-0.238091;,
  0.896217;-0.266271;-0.354818;,
  0.994182;-0.103956;-0.028213;,
  0.992230;0.080776;0.094635;,
  0.609390;-0.099649;0.786583;,
  0.115602;0.987793;0.104411;,
  0.413941;-0.282943;0.865214;,
  0.951824;-0.302594;0.049685;,
  0.273281;0.961851;-0.012661;,
  0.166860;0.974298;-0.151331;,
  0.554471;-0.358784;-0.750890;,
  -0.504214;-0.411293;-0.759346;,
  -0.071366;0.977493;-0.198530;,
  -0.179867;0.983120;0.033503;,
  -0.576620;-0.194781;0.793454;,
  0.003942;0.889597;-0.456729;,
  0.002889;0.944824;-0.327566;,
  0.952670;-0.226459;0.202822;,
  -0.937519;-0.347764;0.010921;,
  -0.987366;0.158289;-0.007311;,
  -0.982167;0.134906;-0.130953;,
  -0.979960;0.078662;-0.183004;,
  -0.958385;0.273975;-0.080220;,
  -0.963171;-0.102793;0.248466;,
  -0.959481;-0.268152;0.086545;,
  -0.668107;0.219884;-0.710834;,
  -0.804467;0.100433;-0.585445;,
  -0.049546;0.063142;-0.996774;,
  0.471644;0.484441;-0.736796;,
  0.000000;-1.000000;0.000000;,
  0.649966;0.034315;0.759188;,
  0.642118;-0.139750;0.753761;,
  -0.975309;0.053551;0.214255;,
  -0.048308;-0.179199;0.982626;,
  -0.026813;0.075674;0.996772;,
  0.030007;-0.160324;0.986608;,
  0.767800;0.154780;-0.621712;,
  0.970384;0.213776;-0.112497;,
  -0.232540;0.969701;-0.074868;,
  0.899718;0.103650;0.423987;,
  -0.001786;0.210672;0.977555;,
  0.997454;0.069010;0.017998;,
  0.939760;-0.006889;-0.341767;,
  0.007707;-0.082772;-0.996539;,
  0.008033;-0.082993;-0.996518;,
  -0.939343;-0.003994;-0.342955;,
  -0.008567;0.206570;0.978394;,
  -0.922855;0.112735;0.368280;,
  -0.999126;0.041586;-0.004275;,
  0.902790;0.107238;0.416497;,
  0.007870;-0.082883;-0.996528;,
  -0.002030;-0.973697;0.227837;,
  0.008086;-0.392741;-0.919613;,
  0.007982;-0.391965;-0.919946;,
  0.008190;-0.393518;-0.919280;,
  0.004505;0.855476;-0.517822;,
  0.006592;0.670200;-0.742151;,
  0.006706;0.670259;-0.742097;,
  0.975866;-0.215648;-0.034385;,
  0.996357;0.004647;0.085159;,
  -0.999960;-0.000734;0.008930;,
  -0.974564;0.214396;-0.065268;,
  -0.903245;-0.347067;0.252375;,
  0.002329;0.965632;-0.259903;,
  0.002933;0.944844;-0.327508;,
  -0.647398;0.123797;-0.752030;,
  0.210694;0.050855;-0.976228;,
  -0.991039;0.040581;-0.127258;,
  0.007809;0.490047;-0.871661;,
  0.007741;0.490140;-0.871609;,
  -0.121702;-0.244198;0.962058;,
  -0.196031;0.100418;0.975442;,
  0.616759;-0.678405;0.399219;,
  -0.230464;-0.060921;0.971172;,
  0.924730;0.327143;-0.194558;,
  0.999984;0.003938;0.004185;,
  0.841733;0.118673;-0.526690;,
  0.210771;-0.115303;0.970712;,
  0.006859;-0.564025;-0.825730;,
  0.007322;-0.565938;-0.824416;,
  -0.228596;-0.115200;0.966681;,
  0.902821;0.107200;0.416440;,
  0.994590;0.034632;-0.097932;,
  0.007870;-0.082885;-0.996528;,
  0.008033;-0.082996;-0.996517;,
  -0.001783;0.210676;0.977554;,
  0.004995;0.214760;0.976654;,
  0.004995;0.214763;0.976653;,
  0.951251;-0.029719;-0.306983;,
  0.951251;-0.029716;-0.306982;,
  -0.987646;0.076083;0.136992;,
  -0.908792;0.137247;0.394031;,
  -0.908801;0.137130;0.394050;,
  -0.939345;-0.004071;-0.342950;,
  -0.941904;0.002142;-0.335876;;
  134;
  3;2,4,3;,
  3;3,4,6;,
  3;2,7,4;,
  3;1,7,2;,
  3;8,9,10;,
  3;8,10,11;,
  3;12,13,14;,
  3;12,14,15;,
  3;16,17,18;,
  3;16,18,74;,
  3;75,76,75;,
  3;75,75,77;,
  3;19,20,21;,
  3;20,22,23;,
  3;10,24,25;,
  3;26,25,27;,
  3;38,78,39;,
  3;79,80,78;,
  3;81,11,40;,
  3;78,38,79;,
  3;82,8,11;,
  3;20,41,34;,
  3;20,34,22;,
  3;19,37,41;,
  3;19,41,20;,
  3;83,42,43;,
  3;83,43,44;,
  3;42,84,45;,
  3;42,45,43;,
  3;85,46,47;,
  3;43,45,48;,
  3;43,48,49;,
  3;49,48,50;,
  3;86,87,39;,
  3;86,39,51;,
  3;48,51,50;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;47,13,12;,
  3;49,88,44;,
  3;49,44,43;,
  3;50,89,88;,
  3;50,88,49;,
  3;40,26,53;,
  3;40,53,54;,
  3;90,42,83;,
  3;91,80,79;,
  3;91,79,92;,
  3;23,21,20;,
  3;21,55,19;,
  3;56,93,94;,
  3;56,94,57;,
  3;95,30,29;,
  3;25,29,27;,
  3;25,26,10;,
  3;57,94,96;,
  3;57,96,58;,
  3;47,90,13;,
  3;90,23,84;,
  3;90,84,42;,
  3;21,23,90;,
  3;21,90,47;,
  3;46,55,21;,
  3;46,21,47;,
  3;40,15,14;,
  3;50,51,59;,
  3;59,51,97;,
  3;59,97,60;,
  3;40,54,15;,
  3;60,97,9;,
  3;60,9,8;,
  3;52,18,17;,
  3;52,17,52;,
  3;98,60,8;,
  3;98,8,82;,
  3;56,27,29;,
  3;39,87,38;,
  3;27,53,26;,
  3;60,98,99;,
  3;60,99,59;,
  3;59,99,89;,
  3;59,89,50;,
  3;26,40,11;,
  3;26,11,10;,
  3;100,54,58;,
  3;101,34,33;,
  3;101,33,102;,
  3;24,33,30;,
  3;24,30,25;,
  3;61,1,0;,
  3;61,0,35;,
  3;36,7,1;,
  3;36,1,61;,
  3;35,0,5;,
  3;35,5,32;,
  3;32,5,6;,
  3;32,6,31;,
  3;31,6,4;,
  3;31,4,28;,
  3;28,4,7;,
  3;28,7,36;,
  3;58,54,53;,
  3;58,53,57;,
  3;57,53,27;,
  3;57,27,56;,
  3;58,96,103;,
  3;12,15,58;,
  3;37,93,56;,
  3;56,29,37;,
  3;72,104,62;,
  4;72,62,29,30;,
  3;72,30,64;,
  4;72,64,105,104;,
  3;73,106,66;,
  4;73,66,33,34;,
  3;73,34,67;,
  4;73,67,107,106;,
  3;63,108,69;,
  4;63,69,37,29;,
  3;63,29,109;,
  4;63,109,110,108;,
  3;65,105,64;,
  4;65,64,30,33;,
  3;65,33,111;,
  4;65,111,112,105;,
  3;70,113,71;,
  4;70,71,41,37;,
  3;70,37,114;,
  4;70,114,115,113;,
  3;68,116,117;,
  4;68,117,34,41;,
  3;68,41,71;,
  4;68,71,113,116;;
 }
 MeshTextureCoords {
  123;
  0.893800;0.043300;,
  0.811000;0.008600;,
  0.805900;0.043400;,
  0.710900;0.013500;,
  0.891500;0.008600;,
  0.981300;0.005600;,
  0.883500;0.401700;,
  0.827300;0.496900;,
  0.830100;0.544900;,
  0.890000;0.429000;,
  0.917000;0.339700;,
  0.914100;0.374200;,
  0.955500;0.373400;,
  0.953400;0.339400;,
  0.913300;0.379300;,
  0.910900;0.388200;,
  0.956600;0.387900;,
  0.955900;0.379300;,
  0.681200;0.593800;,
  0.721900;0.594500;,
  0.716400;0.536700;,
  0.769500;0.593800;,
  0.768800;0.544500;,
  0.829100;0.593800;,
  0.878900;0.593800;,
  0.885200;0.535900;,
  0.923400;0.593800;,
  0.768900;0.496700;,
  0.827300;0.442200;,
  0.990900;0.506600;,
  0.976600;0.503000;,
  0.976600;0.529500;,
  0.991000;0.466400;,
  0.976800;0.465900;,
  0.648900;0.595500;,
  0.648400;0.610400;,
  0.701000;0.610200;,
  0.701000;0.595500;,
  0.939100;0.594900;,
  0.939100;0.610200;,
  0.994500;0.610200;,
  0.994500;0.594900;,
  0.991000;0.466400;,
  0.976800;0.465900;,
  0.976900;0.419100;,
  0.991100;0.418900;,
  0.719500;0.408600;,
  0.768900;0.442100;,
  0.725300;0.382200;,
  0.990700;0.571500;,
  0.976400;0.571800;,
  0.976600;0.529500;,
  0.772100;0.365200;,
  0.754600;0.349000;,
  0.797500;0.335300;,
  0.825000;0.365600;,
  0.905200;0.413200;,
  0.914100;0.436800;,
  0.950000;0.436900;,
  0.960700;0.413400;,
  0.932000;0.446200;,
  0.990900;0.506600;,
  0.977100;0.364700;,
  0.991300;0.364800;,
  0.977100;0.352200;,
  0.991300;0.352000;,
  0.896500;0.454400;,
  0.925800;0.527900;,
  0.929300;0.460900;,
  0.976600;0.503000;,
  0.680500;0.531300;,
  0.645300;0.593800;,
  0.645300;0.531300;,
  0.824600;0.594900;,
  0.824600;0.610200;,
  0.878900;0.610200;,
  0.878900;0.594900;,
  0.678900;0.460900;,
  0.644500;0.460900;,
  0.713300;0.430500;,
  0.706300;0.454700;,
  0.990700;0.571500;,
  0.841400;0.350000;,
  0.873700;0.377000;,
  0.976400;0.571800;,
  0.991100;0.418900;,
  0.976900;0.419100;,
  0.909000;0.594900;,
  0.991300;0.364800;,
  0.977100;0.364700;,
  0.976400;0.577700;,
  0.768200;0.610200;,
  0.768400;0.595300;,
  0.648000;0.734800;,
  0.647700;0.744100;,
  0.701600;0.744100;,
  0.701200;0.734800;,
  0.939700;0.734800;,
  0.940200;0.744500;,
  0.994800;0.744500;,
  0.993900;0.734800;,
  0.768200;0.743900;,
  0.768200;0.734800;,
  0.824200;0.744500;,
  0.824200;0.734800;,
  0.878900;0.744400;,
  0.878900;0.734800;,
  0.963700;0.460900;,
  0.963200;0.527900;,
  0.962600;0.593200;,
  0.824800;0.610660;,
  0.878900;0.632490;,
  0.824600;0.610580;,
  0.736490;0.676000;,
  0.768200;0.641880;,
  0.701160;0.711760;,
  0.902380;0.658310;,
  0.939540;0.701920;,
  0.780090;0.636650;,
  0.993730;0.734420;,
  0.993900;0.734520;,
  0.693070;0.715640;,
  0.648000;0.734520;;
 }
}
