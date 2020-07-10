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
 -1.04241;-1.01373;2.90463;,
 -1.47150;-0.04239;4.65399;,
 1.53213;-1.01844;2.88105;,
 -2.75880;-0.33474;1.96629;,
 2.16399;-0.04239;4.62099;,
 3.39468;-0.33474;1.58907;,
 -1.96188;-9.60027;-2.30577;,
 -2.26839;-11.09031;-4.41822;,
 -3.38592;-15.59343;-3.06966;,
 -3.31989;-15.59343;0.29706;,
 -3.15960;-16.37142;0.62715;,
 3.36165;-16.37142;0.57057;,
 2.46576;-16.37142;6.46938;,
 -1.68840;-16.37142;6.50238;,
 -3.38592;-16.37142;-3.02721;,
 3.32394;-16.37142;-3.08850;,
 3.55971;-15.59343;0.23577;,
 -3.31989;-15.59343;0.29706;,
 3.64458;-10.82628;2.48496;,
 3.36165;-7.44540;2.48496;,
 2.39502;-6.96441;6.12987;,
 2.21112;-9.60027;-2.34348;,
 2.23941;-7.55385;-1.19295;,
 -3.02757;-7.44540;2.73960;,
 -1.47624;-7.55385;-1.15995;,
 -1.56111;-6.96441;6.16290;,
 -3.50850;-10.82628;2.75844;,
 -2.70690;-12.49548;-7.69536;,
 2.16870;-11.09031;-4.45593;,
 -3.40479;-15.59343;2.70657;,
 -3.31989;-15.59343;0.29706;,
 -3.15960;-16.37142;0.62715;,
 -3.38592;-15.59343;-3.06966;,
 -3.38592;-16.37142;-3.02721;,
 2.53650;-6.88428;-1.65033;,
 4.05480;-6.83715;2.60757;,
 3.36165;-7.44540;2.48496;,
 2.23941;-7.55385;-1.19295;,
 4.05480;-6.83715;2.60757;,
 2.54118;-6.29955;6.60141;,
 2.39502;-6.96441;6.12987;,
 3.36165;-7.44540;2.48496;,
 3.53142;-15.59343;-7.38414;,
 3.32394;-15.59343;-3.12624;,
 3.32394;-16.37142;-3.08850;,
 3.53142;-16.37142;-7.40301;,
 2.55537;-12.49548;-7.74249;,
 3.32394;-15.59343;-3.12624;,
 3.53142;-15.59343;-7.38414;,
 3.83319;-15.59343;2.64528;,
 2.75811;-15.59343;6.49296;,
 2.46576;-16.37142;6.46938;,
 1.34823;-13.84875;-12.75957;,
 1.90935;-15.59343;-12.30690;,
 -0.39171;-15.59343;-13.42914;,
 -1.80630;-13.84875;-12.73128;,
 -2.54661;-16.37142;-12.25974;,
 2.09796;-16.37142;-12.30219;,
 3.53142;-16.37142;-7.40301;,
 -4.04133;-16.37142;-7.33698;,
 -0.39171;-16.37142;-13.44327;,
 3.36165;-16.37142;0.57057;,
 2.09796;-16.37142;-12.30219;,
 1.90935;-15.59343;-12.30690;,
 -0.39171;-16.37142;-13.44327;,
 -0.39171;-15.59343;-13.42914;,
 -1.96662;-11.01486;6.69573;,
 -3.40479;-15.59343;2.70657;,
 -1.96188;-15.59343;6.53541;,
 3.55971;-15.59343;0.23577;,
 2.73924;-11.01486;6.65328;,
 0.41931;-6.96441;6.37980;,
 0.39105;-11.01486;7.21440;,
 -1.76385;-6.29955;6.63912;,
 -3.57453;-6.83715;2.92821;,
 -3.02757;-7.44540;2.73960;,
 -1.56111;-6.96441;6.16290;,
 2.75811;-15.59343;6.49296;,
 0.40518;-15.59343;7.04937;,
 3.55971;-15.59343;0.23577;,
 3.83319;-15.59343;2.64528;,
 -1.68840;-16.37142;6.50238;,
 -2.35800;-15.59343;-12.26919;,
 -4.04133;-15.59343;-7.31811;,
 -1.96188;-15.59343;6.53541;,
 -4.04133;-15.59343;-7.31811;,
 -4.04133;-16.37142;-7.33698;,
 0.41931;-6.96441;6.37980;,
 -2.54661;-16.37142;-12.25974;,
 -2.35800;-15.59343;-12.26919;,
 0.40518;-15.59343;7.04937;,
 -1.73085;-6.88428;-1.61733;,
 -1.47624;-7.55385;-1.15995;,
 2.10741;-0.43374;-1.82010;,
 3.39468;-0.33474;1.58907;,
 3.78132;-0.42432;1.69281;,
 2.33373;-0.52335;-2.17845;,
 3.39468;-0.33474;1.58907;,
 2.16399;-0.04239;4.62099;,
 2.16870;-0.07536;5.29056;,
 3.78132;-0.42432;1.69281;,
 -1.52808;-0.43374;-1.78710;,
 -1.75914;-0.52335;-2.14545;,
 -2.75880;-0.33474;1.96629;,
 -3.14544;-0.42432;2.14074;,
 -1.47150;-0.04239;4.65399;,
 -1.69314;-0.16497;5.29056;,
 0.40518;-15.59343;7.04937;,
 0.39105;-11.01486;7.21440;,
 0.41931;-6.96441;6.37980;,
 -1.75119;-5.20194;6.39783;,
 -3.56757;-6.81249;2.93694;,
 -3.57321;-6.81750;2.92581;,
 -1.73805;-5.26689;-1.75161;,
 0.26814;-3.52533;-1.91178;,
 2.37123;-1.69974;-2.08077;,
 2.26701;-1.71798;5.63652;,
 -0.24546;-3.89634;6.11844;,
 -2.03118;-5.51280;-0.81948;,
 3.78192;-0.43872;1.69485;,
 3.77748;-0.44244;1.70796;,
 2.59884;-1.49598;-1.44117;,
 3.78192;-0.43872;1.69485;;
 
 134;
 3;0,1,2;,
 3;3,1,0;,
 3;1,4,2;,
 3;2,4,5;,
 3;6,7,8;,
 3;9,6,8;,
 3;10,11,12;,
 3;13,10,12;,
 3;14,15,16;,
 3;17,14,16;,
 3;11,10,17;,
 3;16,11,17;,
 3;18,19,20;,
 3;21,22,19;,
 3;23,24,6;,
 3;25,23,26;,
 3;27,7,28;,
 3;7,6,21;,
 3;29,30,31;,
 3;21,28,7;,
 3;30,32,33;,
 3;34,35,36;,
 3;37,34,36;,
 3;38,39,40;,
 3;41,38,40;,
 3;42,43,44;,
 3;45,42,44;,
 3;46,28,47;,
 3;48,46,47;,
 3;49,50,51;,
 3;52,46,48;,
 3;53,52,48;,
 3;54,52,53;,
 3;27,46,52;,
 3;55,27,52;,
 3;54,55,52;,
 3;56,57,58;,
 3;59,56,58;,
 3;56,60,57;,
 3;51,61,49;,
 3;45,62,63;,
 3;42,45,63;,
 3;62,64,65;,
 3;63,62,65;,
 3;66,26,67;,
 3;68,66,67;,
 3;44,43,69;,
 3;21,6,24;,
 3;22,21,24;,
 3;19,18,21;,
 3;20,70,18;,
 3;70,20,71;,
 3;72,70,71;,
 3;73,74,75;,
 3;76,73,75;,
 3;6,26,23;,
 3;77,70,72;,
 3;78,77,72;,
 3;61,69,49;,
 3;28,21,79;,
 3;47,28,79;,
 3;79,21,18;,
 3;80,79,18;,
 3;18,70,77;,
 3;80,18,77;,
 3;31,81,29;,
 3;82,55,54;,
 3;27,55,82;,
 3;83,27,82;,
 3;81,84,29;,
 3;7,27,83;,
 3;8,7,83;,
 3;15,14,59;,
 3;58,15,59;,
 3;32,85,86;,
 3;33,32,86;,
 3;73,76,87;,
 3;28,46,27;,
 3;26,66,25;,
 3;88,86,85;,
 3;89,88,85;,
 3;64,88,89;,
 3;65,64,89;,
 3;9,67,26;,
 3;6,9,26;,
 3;90,84,81;,
 3;91,34,37;,
 3;92,91,37;,
 3;74,91,92;,
 3;75,74,92;,
 3;93,94,95;,
 3;96,93,95;,
 3;97,98,99;,
 3;100,97,99;,
 3;101,93,96;,
 3;102,101,96;,
 3;103,101,102;,
 3;104,103,102;,
 3;105,103,104;,
 3;106,105,104;,
 3;98,105,106;,
 3;99,98,106;,
 3;66,68,107;,
 3;108,66,107;,
 3;25,66,108;,
 3;109,25,108;,
 3;51,50,90;,
 3;90,81,51;,
 3;87,40,39;,
 3;39,73,87;,
 3;110,106,111;,
 4;74,73,110,111;,
 3;112,74,111;,
 4;106,104,112,111;,
 3;113,102,114;,
 4;34,91,113,114;,
 3;115,34,114;,
 4;102,96,115,114;,
 3;116,99,117;,
 4;73,39,116,117;,
 3;110,73,117;,
 4;99,106,110,117;,
 3;112,104,118;,
 4;91,74,112,118;,
 3;113,91,118;,
 4;104,102,113,118;,
 3;119,100,120;,
 4;39,38,119,120;,
 3;116,39,120;,
 4;100,99,116,120;,
 3;115,96,121;,
 4;35,34,115,121;,
 3;122,35,121;,
 4;96,95,122,121;;
 
 MeshMaterialList {
  11;
  134;
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9;;
  Material {
   0.119200;0.106400;0.530400;1.000000;;
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
   0.548800;0.627200;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.385600;0.000000;0.056800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.511200;0.395200;0.000000;1.000000;;
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
   0.000000;0.467200;0.336000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.222400;0.380000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  119;
  0.157969;0.974501;-0.159354;,
  0.084713;0.991845;-0.095227;,
  -0.173488;0.884896;-0.432273;,
  0.255800;0.870449;-0.420577;,
  -0.009932;0.982321;-0.186941;,
  -0.076320;0.977590;-0.196198;,
  -0.059419;0.988102;-0.141855;,
  -0.040850;0.993684;-0.104519;,
  -0.988953;0.125960;0.078139;,
  -0.952577;0.303173;0.026124;,
  -0.958219;0.222796;-0.179382;,
  -0.997966;0.019017;-0.060848;,
  0.202148;-0.943545;0.262409;,
  0.637332;-0.770589;-0.000688;,
  -0.251798;-0.965724;0.063052;,
  -0.476191;-0.784363;0.397513;,
  0.002055;-0.973709;0.227786;,
  0.000697;-0.997080;0.076359;,
  0.001378;-0.988264;0.152753;,
  0.915430;-0.271721;0.296910;,
  0.943268;-0.317293;-0.097825;,
  0.996748;0.066888;0.044936;,
  0.939104;-0.198214;-0.280704;,
  0.963158;0.125055;-0.238091;,
  -0.896217;-0.266271;-0.354818;,
  -0.994182;-0.103956;-0.028213;,
  -0.992230;0.080776;0.094635;,
  -0.609390;-0.099650;0.786583;,
  -0.115602;0.987793;0.104411;,
  -0.413947;-0.282942;0.865212;,
  -0.951825;-0.302595;0.049658;,
  -0.273282;0.961851;-0.012661;,
  -0.166859;0.974298;-0.151331;,
  -0.554460;-0.358783;-0.750899;,
  0.504215;-0.411294;-0.759345;,
  0.071366;0.977493;-0.198529;,
  0.179868;0.983120;0.033504;,
  0.576622;-0.194782;0.793453;,
  -0.003942;0.889597;-0.456729;,
  -0.002889;0.944824;-0.327566;,
  -0.952670;-0.226459;0.202822;,
  0.937518;-0.347764;0.010919;,
  0.987366;0.158289;-0.007311;,
  0.982167;0.134906;-0.130953;,
  0.979960;0.078662;-0.183004;,
  0.958385;0.273975;-0.080219;,
  0.963171;-0.102793;0.248466;,
  0.959481;-0.268152;0.086545;,
  0.668107;0.219884;-0.710834;,
  0.804467;0.100434;-0.585445;,
  0.049546;0.063142;-0.996774;,
  -0.471644;0.484442;-0.736796;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.649966;0.034315;0.759188;,
  -0.642118;-0.139750;0.753761;,
  0.975309;0.053551;0.214255;,
  0.048308;-0.179199;0.982626;,
  0.026813;0.075674;0.996772;,
  -0.030007;-0.160324;0.986608;,
  -0.767800;0.154780;-0.621712;,
  -0.970384;0.213776;-0.112497;,
  0.232540;0.969701;-0.074868;,
  -0.899726;0.103657;0.423967;,
  0.001788;0.210670;0.977556;,
  -0.997454;0.069006;0.017969;,
  -0.939752;-0.006891;-0.341787;,
  -0.007707;-0.082772;-0.996539;,
  -0.008033;-0.082993;-0.996518;,
  0.939343;-0.003995;-0.342955;,
  0.008566;0.206571;0.978394;,
  0.922859;0.112734;0.368269;,
  0.999126;0.041584;-0.004287;,
  -0.902798;0.107240;0.416480;,
  -0.007870;-0.082883;-0.996528;,
  0.002030;-0.973697;0.227837;,
  -0.008086;-0.392741;-0.919613;,
  -0.007982;-0.391964;-0.919946;,
  -0.008190;-0.393518;-0.919280;,
  -0.004505;0.855476;-0.517822;,
  -0.006706;0.670259;-0.742097;,
  -0.006592;0.670200;-0.742152;,
  -0.975866;-0.215648;-0.034385;,
  -0.996357;0.004647;0.085159;,
  0.999960;-0.000734;0.008930;,
  0.974564;0.214396;-0.065268;,
  0.903245;-0.347067;0.252376;,
  -0.002933;0.944844;-0.327507;,
  -0.002329;0.965632;-0.259903;,
  0.647398;0.123797;-0.752030;,
  -0.210695;0.050855;-0.976228;,
  0.991039;0.040581;-0.127258;,
  -0.007809;0.490047;-0.871661;,
  -0.007741;0.490140;-0.871609;,
  0.196031;0.100418;0.975443;,
  0.121702;-0.244198;0.962058;,
  -0.616759;-0.678404;0.399219;,
  0.230463;-0.060921;0.971172;,
  -0.924730;0.327143;-0.194557;,
  -0.999984;0.003938;0.004185;,
  -0.841733;0.118672;-0.526690;,
  -0.210771;-0.115302;0.970712;,
  -0.006859;-0.564025;-0.825729;,
  -0.007322;-0.565938;-0.824415;,
  0.228596;-0.115200;0.966681;,
  -0.902824;0.107200;0.416435;,
  -0.994590;0.034632;-0.097935;,
  -0.007870;-0.082885;-0.996528;,
  -0.008033;-0.082996;-0.996517;,
  0.001787;0.210673;0.977555;,
  -0.004991;0.214757;0.976655;,
  -0.004987;0.214756;0.976655;,
  -0.951251;-0.029719;-0.306983;,
  -0.951251;-0.029716;-0.306982;,
  0.987648;0.076084;0.136980;,
  0.908792;0.137251;0.394031;,
  0.908801;0.137139;0.394049;,
  0.941904;0.002139;-0.335875;,
  0.939345;-0.004069;-0.342950;;
  134;
  3;3,4,2;,
  3;6,4,3;,
  3;4,7,2;,
  3;2,7,1;,
  3;10,9,8;,
  3;11,10,8;,
  3;14,13,12;,
  3;15,14,12;,
  3;18,17,16;,
  3;75,18,16;,
  3;76,77,76;,
  3;78,76,76;,
  3;21,20,19;,
  3;23,22,20;,
  3;25,24,10;,
  3;27,25,26;,
  3;39,79,38;,
  3;79,80,81;,
  3;40,11,82;,
  3;81,38,79;,
  3;11,8,83;,
  3;34,41,20;,
  3;22,34,20;,
  3;41,37,19;,
  3;20,41,19;,
  3;43,42,84;,
  3;44,43,84;,
  3;45,85,42;,
  3;43,45,42;,
  3;47,46,86;,
  3;48,45,43;,
  3;49,48,43;,
  3;50,48,49;,
  3;39,87,88;,
  3;51,39,88;,
  3;50,51,48;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,53,52;,
  3;12,13,47;,
  3;44,89,49;,
  3;43,44,49;,
  3;89,90,50;,
  3;49,89,50;,
  3;54,26,40;,
  3;55,54,40;,
  3;84,42,91;,
  3;81,80,92;,
  3;93,81,92;,
  3;20,21,23;,
  3;19,56,21;,
  3;94,95,57;,
  3;58,94,57;,
  3;29,30,96;,
  3;27,29,25;,
  3;10,26,25;,
  3;97,94,58;,
  3;59,97,58;,
  3;13,91,47;,
  3;85,23,91;,
  3;42,85,91;,
  3;91,23,21;,
  3;47,91,21;,
  3;21,56,46;,
  3;47,21,46;,
  3;14,15,40;,
  3;60,51,50;,
  3;98,51,60;,
  3;61,98,60;,
  3;15,55,40;,
  3;9,98,61;,
  3;8,9,61;,
  3;17,18,52;,
  3;52,17,52;,
  3;8,61,99;,
  3;83,8,99;,
  3;29,27,57;,
  3;38,87,39;,
  3;26,54,27;,
  3;100,99,61;,
  3;60,100,61;,
  3;90,100,60;,
  3;50,90,60;,
  3;11,40,26;,
  3;10,11,26;,
  3;59,55,101;,
  3;33,34,102;,
  3;103,33,102;,
  3;30,33,24;,
  3;25,30,24;,
  3;0,1,62;,
  3;35,0,62;,
  3;1,7,36;,
  3;62,1,36;,
  3;5,0,35;,
  3;32,5,35;,
  3;6,5,32;,
  3;31,6,32;,
  3;4,6,31;,
  3;28,4,31;,
  3;7,4,28;,
  3;36,7,28;,
  3;54,55,59;,
  3;58,54,59;,
  3;27,54,58;,
  3;57,27,58;,
  3;104,97,59;,
  3;59,15,12;,
  3;57,95,37;,
  3;37,29,57;,
  3;63,105,73;,
  4;30,29,63,73;,
  3;65,30,73;,
  4;105,106,65,73;,
  3;67,107,74;,
  4;34,33,67,74;,
  3;68,34,74;,
  4;107,108,68,74;,
  3;70,109,64;,
  4;29,37,70,64;,
  3;110,29,64;,
  4;109,111,110,64;,
  3;65,106,66;,
  4;33,30,65,66;,
  3;112,33,66;,
  4;106,113,112,66;,
  3;72,114,71;,
  4;37,41,72,71;,
  3;115,37,71;,
  4;114,116,115,71;,
  3;117,118,69;,
  4;41,34,117,69;,
  3;72,41,69;,
  4;118,114,72,69;;
 }
 MeshTextureCoords {
  123;
  0.805900;0.043400;,
  0.811000;0.008600;,
  0.893800;0.043300;,
  0.710900;0.013500;,
  0.891500;0.008600;,
  0.981300;0.005600;,
  0.830100;0.544900;,
  0.827300;0.496900;,
  0.883500;0.401700;,
  0.890000;0.429000;,
  0.955500;0.373400;,
  0.914100;0.374200;,
  0.917000;0.339700;,
  0.953400;0.339400;,
  0.956600;0.387900;,
  0.910900;0.388200;,
  0.913300;0.379300;,
  0.955900;0.379300;,
  0.716400;0.536700;,
  0.721900;0.594500;,
  0.681200;0.593800;,
  0.768800;0.544500;,
  0.769500;0.593800;,
  0.878900;0.593800;,
  0.829100;0.593800;,
  0.923400;0.593800;,
  0.885200;0.535900;,
  0.827300;0.442200;,
  0.768900;0.496700;,
  0.976600;0.529500;,
  0.976600;0.503000;,
  0.990900;0.506600;,
  0.976800;0.465900;,
  0.991000;0.466400;,
  0.701000;0.610200;,
  0.648400;0.610400;,
  0.648900;0.595500;,
  0.701000;0.595500;,
  0.994500;0.610200;,
  0.939100;0.610200;,
  0.939100;0.594900;,
  0.994500;0.594900;,
  0.976900;0.419100;,
  0.976800;0.465900;,
  0.991000;0.466400;,
  0.991100;0.418900;,
  0.768900;0.442100;,
  0.719500;0.408600;,
  0.725300;0.382200;,
  0.976600;0.529500;,
  0.976400;0.571800;,
  0.990700;0.571500;,
  0.772100;0.365200;,
  0.754600;0.349000;,
  0.797500;0.335300;,
  0.825000;0.365600;,
  0.950000;0.436900;,
  0.914100;0.436800;,
  0.905200;0.413200;,
  0.960700;0.413400;,
  0.932000;0.446200;,
  0.990900;0.506600;,
  0.991300;0.364800;,
  0.977100;0.364700;,
  0.991300;0.352000;,
  0.977100;0.352200;,
  0.925800;0.527900;,
  0.896500;0.454400;,
  0.929300;0.460900;,
  0.976600;0.503000;,
  0.680500;0.531300;,
  0.645300;0.593800;,
  0.645300;0.531300;,
  0.878900;0.610200;,
  0.824600;0.610200;,
  0.824600;0.594900;,
  0.878900;0.594900;,
  0.678900;0.460900;,
  0.644500;0.460900;,
  0.713300;0.430500;,
  0.706300;0.454700;,
  0.990700;0.571500;,
  0.841400;0.350000;,
  0.873700;0.377000;,
  0.976400;0.571800;,
  0.976900;0.419100;,
  0.991100;0.418900;,
  0.909000;0.594900;,
  0.991300;0.364800;,
  0.977100;0.364700;,
  0.976400;0.577700;,
  0.768200;0.610200;,
  0.768400;0.595300;,
  0.701600;0.744100;,
  0.647700;0.744100;,
  0.648000;0.734800;,
  0.701200;0.734800;,
  0.994800;0.744500;,
  0.940200;0.744500;,
  0.939700;0.734800;,
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
  0.878900;0.632490;,
  0.824800;0.610660;,
  0.824600;0.610580;,
  0.768200;0.641880;,
  0.736490;0.676000;,
  0.701160;0.711760;,
  0.939540;0.701920;,
  0.902380;0.658310;,
  0.780090;0.636650;,
  0.993900;0.734520;,
  0.993730;0.734420;,
  0.693070;0.715640;,
  0.648000;0.734520;;
 }
}
