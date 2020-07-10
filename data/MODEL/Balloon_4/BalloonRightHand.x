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
 143;
 -14.10168;-1.15179;1.43100;,
 -14.62506;-0.93018;-0.15336;,
 -14.22429;-1.30272;-0.15807;,
 -13.28121;0.11661;1.90722;,
 -13.62069;0.46554;-0.21936;,
 -6.38271;-0.77457;-1.01625;,
 -6.39216;0.96537;-1.14828;,
 -5.38779;0.30051;0.57282;,
 -6.37800;0.97008;2.09112;,
 -6.36858;-0.63780;2.09586;,
 -6.37329;-1.02921;0.56808;,
 -6.38745;1.63491;0.59166;,
 -10.32000;-0.92073;-1.13883;,
 -8.58003;-1.38285;-0.21936;,
 -8.50932;-0.81702;0.56808;,
 -6.37329;-1.02921;0.56808;,
 -8.12739;-1.93926;-1.19070;,
 -13.28121;-0.08142;-0.37497;,
 -12.08352;-0.08142;-0.37968;,
 -12.08823;0.96537;-0.36552;,
 -13.67259;0.71073;-0.37026;,
 -14.91270;-0.42564;-0.39384;,
 -14.49306;-0.79344;-0.39855;,
 -6.38271;-0.77457;-1.01625;,
 -13.22934;-0.36435;-0.26181;,
 -13.28121;-0.02013;-1.03983;,
 -12.08352;0.04116;-1.18599;,
 -12.08352;-0.08142;-0.37968;,
 -13.28121;-0.08142;-0.37497;,
 -14.49306;-0.74628;-0.87951;,
 -14.49306;-0.79344;-0.39855;,
 -11.58840;-2.21745;-1.90743;,
 -11.58369;-1.74123;-1.57737;,
 -12.84738;-1.85439;-1.58679;,
 -11.47995;-2.21274;-2.54400;,
 -12.81441;-2.25048;-2.04417;,
 -12.81441;-1.87326;-2.21394;,
 -11.47995;-1.69407;-2.55813;,
 -11.47995;-1.22727;-2.06775;,
 -12.81441;-1.57146;-1.88385;,
 -12.84738;-1.85439;-1.58679;,
 -11.58369;-1.74123;-1.57737;,
 -9.61269;-1.28382;-2.57700;,
 -9.99936;-0.39735;-2.00646;,
 -10.32000;-0.92073;-1.13883;,
 -10.16910;-2.16090;-1.64337;,
 -11.47995;-2.21274;-2.54400;,
 -9.60798;-2.01468;-2.31765;,
 -9.60798;-2.01468;-2.31765;,
 -8.18868;-1.67517;-1.92159;,
 -8.18868;-0.61425;-2.12433;,
 -6.38271;-0.77457;-1.01625;,
 -13.70088;-1.43943;1.38384;,
 -12.88512;-0.47280;1.91667;,
 -13.28121;-0.02013;-1.03983;,
 -14.49306;-0.74628;-0.87951;,
 -14.90796;-0.43509;-0.87480;,
 -13.67730;0.69660;-1.03038;,
 -13.70088;-1.43943;1.38384;,
 -14.22429;-1.30272;-0.15807;,
 -13.22934;-0.36435;-0.26181;,
 -12.88512;-0.47280;1.91667;,
 -11.74401;0.61173;2.20902;,
 -11.73456;-0.16158;2.21373;,
 -12.08352;0.04116;-1.18599;,
 -12.08823;0.94179;-1.17186;,
 -11.73456;-0.16158;2.21373;,
 -12.08823;-0.02013;-0.29952;,
 -10.13610;0.95595;2.52021;,
 -10.12668;-0.37848;2.52966;,
 -12.09294;0.95124;-0.29952;,
 -10.12668;-0.37848;2.52966;,
 -10.64064;-0.52467;-0.27594;,
 -10.65006;1.25298;-0.26181;,
 -10.33887;0.80031;-1.34160;,
 -8.18868;-1.67517;-1.92159;,
 -8.52348;0.96063;-1.29915;,
 -6.39216;0.96537;-1.14828;,
 -8.50932;0.96537;2.52495;,
 -8.50461;-0.69915;2.53437;,
 -8.52348;1.47459;0.31818;,
 -8.50461;-0.69915;2.53437;,
 -6.37800;0.97008;2.09112;,
 -6.36858;-0.63780;2.09586;,
 -6.38745;1.63491;0.59166;,
 -6.36858;-0.63780;2.09586;,
 -10.64064;-0.52467;-0.27594;,
 -12.08823;-0.02013;-0.29952;,
 -13.62069;0.46554;-0.21936;,
 -12.08823;0.96537;-0.36552;,
 -10.64064;-0.52467;-0.27594;,
 -10.65006;1.25298;-0.26181;,
 -12.81441;-2.25048;-2.04417;,
 -2.05410;2.18664;0.39363;,
 -2.14368;1.28598;2.44005;,
 -0.67722;1.30017;2.52966;,
 -0.46974;2.40351;0.36534;,
 -0.01236;1.19643;-1.65282;,
 -2.19084;-1.56204;0.37476;,
 -2.13897;-0.87360;2.45892;,
 -3.99207;-0.69444;2.30331;,
 -4.00623;-0.69444;-1.19544;,
 -2.22384;-0.91605;-1.81785;,
 -2.19084;-1.56204;0.37476;,
 -4.01565;1.20582;-1.15770;,
 -4.01565;1.91313;0.56808;,
 -2.23800;1.31901;-1.77540;,
 -0.01236;-0.84534;-1.62924;,
 0.22812;1.08795;-1.44534;,
 0.21867;-0.72741;-1.42647;,
 -0.43203;-1.55733;0.32760;,
 -0.03594;-1.56204;0.33234;,
 -0.05952;2.07348;0.36063;,
 -4.00152;1.20582;2.29389;,
 -0.66309;-0.88302;2.51079;,
 -4.01565;1.91313;0.56808;,
 -4.01565;1.20582;-1.15770;,
 -6.39216;0.96537;-1.14828;,
 -6.38745;1.63491;0.59166;,
 -4.00623;-0.69444;-1.19544;,
 -6.38271;-0.77457;-1.01625;,
 -0.43203;-1.55733;0.32760;,
 -0.03594;-1.56204;0.33234;,
 -0.41316;-0.75573;2.30331;,
 -3.99207;-1.08579;0.54453;,
 -6.37329;-1.02921;0.56808;,
 -3.99207;-1.08579;0.54453;,
 -3.99207;-0.69444;2.30331;,
 -6.36858;-0.63780;2.09586;,
 -6.37329;-1.02921;0.56808;,
 -0.42732;1.18698;2.32218;,
 -3.99207;-1.08579;0.54453;,
 -3.99207;-1.08579;0.54453;,
 -4.00152;1.20582;2.29389;,
 -6.37800;0.97008;2.09112;,
 -6.38745;1.63491;0.59166;,
 -6.39216;0.96537;-1.14828;,
 -5.10015;0.31464;0.51150;,
 -6.37329;-1.02921;0.56808;,
 -6.36858;-0.63780;2.09586;,
 -6.38271;-0.77457;-1.01625;,
 -6.37800;0.97008;2.09112;,
 -6.37800;0.97008;2.09112;;
 
 168;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,7;,
 3;7,8,9;,
 3;7,10,5;,
 3;7,11,8;,
 3;6,11,7;,
 3;9,10,7;,
 3;12,13,14;,
 3;15,13,16;,
 3;17,18,19;,
 3;20,17,19;,
 3;21,22,17;,
 3;20,21,17;,
 3;16,23,15;,
 3;24,2,1;,
 3;4,24,1;,
 3;25,26,27;,
 3;28,25,27;,
 3;29,25,28;,
 3;30,29,28;,
 3;31,32,33;,
 3;34,35,36;,
 3;37,34,36;,
 3;38,39,40;,
 3;41,38,40;,
 3;37,36,39;,
 3;38,37,39;,
 3;42,37,38;,
 3;43,42,38;,
 3;43,38,41;,
 3;44,43,41;,
 3;45,31,46;,
 3;47,45,46;,
 3;12,32,31;,
 3;45,12,31;,
 3;48,34,37;,
 3;42,48,37;,
 3;39,36,40;,
 3;49,50,51;,
 3;45,16,13;,
 3;50,49,48;,
 3;42,50,48;,
 3;35,40,36;,
 3;3,0,52;,
 3;53,3,52;,
 3;1,0,3;,
 3;54,55,56;,
 3;57,54,56;,
 3;57,56,21;,
 3;20,57,21;,
 3;58,59,60;,
 3;61,58,60;,
 3;62,3,53;,
 3;63,62,53;,
 3;4,3,62;,
 3;64,54,57;,
 3;65,64,57;,
 3;65,57,20;,
 3;19,65,20;,
 3;66,61,60;,
 3;67,66,60;,
 3;68,62,63;,
 3;69,68,63;,
 3;70,62,68;,
 3;71,66,67;,
 3;72,71,67;,
 3;65,19,73;,
 3;44,64,65;,
 3;74,44,65;,
 3;72,27,26;,
 3;12,72,26;,
 3;2,52,0;,
 3;23,16,75;,
 3;50,76,77;,
 3;44,74,43;,
 3;45,47,75;,
 3;16,45,75;,
 3;43,74,76;,
 3;78,68,69;,
 3;79,78,69;,
 3;80,73,68;,
 3;76,74,73;,
 3;80,76,73;,
 3;50,42,43;,
 3;14,72,12;,
 3;81,71,72;,
 3;14,81,72;,
 3;82,78,79;,
 3;83,82,79;,
 3;84,80,78;,
 3;77,76,80;,
 3;84,77,80;,
 3;77,51,50;,
 3;15,14,13;,
 3;85,81,14;,
 3;15,85,14;,
 3;86,87,70;,
 3;73,86,70;,
 3;87,24,88;,
 3;70,87,88;,
 3;89,18,90;,
 3;91,89,90;,
 3;68,78,80;,
 3;78,82,84;,
 3;92,46,31;,
 3;56,55,22;,
 3;21,56,22;,
 3;33,92,31;,
 3;62,70,4;,
 3;68,73,70;,
 3;13,12,45;,
 3;76,50,43;,
 3;73,74,65;,
 3;93,94,95;,
 3;93,96,97;,
 3;98,99,100;,
 3;101,102,103;,
 3;104,105,93;,
 3;93,106,104;,
 3;107,97,108;,
 3;109,107,108;,
 3;107,110,103;,
 3;102,107,103;,
 3;97,107,102;,
 3;106,97,102;,
 3;97,106,93;,
 3;107,109,111;,
 3;112,108,97;,
 3;112,96,95;,
 3;95,96,93;,
 3;113,94,93;,
 3;114,95,94;,
 3;99,114,94;,
 3;115,116,117;,
 3;118,115,117;,
 3;111,110,107;,
 3;116,119,120;,
 3;117,116,120;,
 3;114,121,122;,
 3;123,114,122;,
 3;119,124,125;,
 3;120,119,125;,
 3;126,127,128;,
 3;129,126,128;,
 3;95,130,112;,
 3;97,96,112;,
 3;95,114,123;,
 3;130,95,123;,
 3;121,114,99;,
 3;98,121,99;,
 3;100,131,98;,
 3;113,100,99;,
 3;94,113,99;,
 3;93,105,113;,
 3;101,104,106;,
 3;102,101,106;,
 3;103,132,101;,
 3;133,115,118;,
 3;134,133,118;,
 3;135,136,137;,
 3;138,139,137;,
 3;137,140,138;,
 3;137,141,135;,
 3;136,140,137;,
 3;139,142,137;,
 3;127,133,134;,
 3;128,127,134;;
 
 MeshMaterialList {
  9;
  168;
  0,
  0,
  4,
  4,
  4,
  4,
  4,
  4,
  0,
  0,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  0,
  0,
  0,
  0,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  0,
  0,
  4,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  4,
  4,
  4,
  4,
  4,
  4,
  6,
  6;;
  Material {
   0.800000;0.677600;0.627200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.536800;0.690400;1.000000;;
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
   0.254400;0.254400;0.254400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
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
   0.800000;0.112800;0.455200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.467200;0.078400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.034400;0.034400;0.034400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  162;
  -0.623625;-0.772229;0.121464;,
  -0.675056;-0.727742;0.121207;,
  -0.490912;0.846554;0.205797;,
  -0.690321;0.672245;0.267477;,
  0.960450;-0.187340;-0.206008;,
  0.286405;0.659837;-0.694685;,
  0.586576;-0.538883;-0.604594;,
  0.539056;-0.177757;0.823299;,
  0.284676;0.382901;0.878833;,
  0.326034;-0.945345;0.005027;,
  0.214372;0.973203;0.083191;,
  -0.177062;-0.931985;0.316311;,
  -0.232844;-0.761326;0.605117;,
  -0.321827;-0.688314;0.650116;,
  0.278829;-0.959574;0.038361;,
  -0.036064;-0.010636;0.999293;,
  -0.036028;-0.013679;0.999257;,
  -0.003609;-0.012974;0.999909;,
  -0.005612;-0.008718;0.999946;,
  -0.007143;-0.020952;0.999755;,
  -0.008240;-0.015756;0.999842;,
  -0.060792;-0.002010;-0.998149;,
  -0.249914;-0.967894;-0.026900;,
  0.184273;-0.976662;-0.110342;,
  0.505323;-0.859053;-0.081711;,
  -0.003744;-0.669220;0.743055;,
  0.064865;-0.568874;0.819863;,
  -0.001684;-0.801329;0.598221;,
  -0.312380;0.112256;-0.943301;,
  -0.313336;-0.389740;-0.865981;,
  -0.150925;-0.153102;-0.976617;,
  -0.144451;0.330807;-0.932577;,
  -0.093406;0.726110;0.681205;,
  -0.190414;0.707317;0.680768;,
  0.024163;0.250467;-0.967823;,
  -0.058913;0.489189;-0.870186;,
  0.116506;-0.993185;0.002990;,
  0.177858;-0.981912;-0.064922;,
  0.282721;0.121239;-0.951509;,
  0.414279;-0.703133;-0.577907;,
  -0.222272;-0.256445;0.940655;,
  -0.253689;-0.102759;0.961812;,
  -0.084751;-0.063224;-0.994394;,
  -0.100295;-0.024870;-0.994647;,
  -0.201740;-0.029086;0.979007;,
  -0.211267;0.004026;0.977420;,
  -0.053859;-0.028945;-0.998129;,
  -0.058958;-0.998230;-0.007851;,
  -0.129112;0.005456;0.991615;,
  -0.065871;0.006128;0.997809;,
  -0.244637;0.956750;0.157427;,
  -0.285996;-0.951842;0.110469;,
  -0.101102;0.984332;-0.144461;,
  -0.046496;0.639046;-0.767762;,
  -0.005625;0.757535;-0.652770;,
  0.065200;0.006304;0.997852;,
  0.133493;0.005301;0.991036;,
  -0.046182;0.996711;-0.066591;,
  0.461319;0.621913;0.632779;,
  -0.052125;0.914871;0.400367;,
  -0.097265;0.995257;-0.001459;,
  0.258433;0.655825;-0.709300;,
  0.140731;0.977515;-0.157031;,
  -0.130831;-0.959747;0.248533;,
  -0.041041;-0.950668;0.307483;,
  -0.115505;-0.992482;-0.040477;,
  -0.079378;-0.956531;-0.280620;,
  -0.122154;-0.968505;-0.216972;,
  -0.121826;0.989656;-0.075761;,
  -0.145484;0.918282;-0.368229;,
  -0.055053;0.928667;-0.366807;,
  0.699748;0.263060;-0.664193;,
  0.573229;-0.221203;-0.788973;,
  0.710168;-0.420969;-0.564311;,
  -0.007186;-0.998956;0.045122;,
  0.353957;-0.935013;0.021588;,
  0.688123;-0.232763;0.687246;,
  0.687131;0.348635;0.637420;,
  0.645238;0.761880;0.056631;,
  -0.098551;0.915680;0.389637;,
  0.192797;-0.001019;0.981238;,
  -0.121128;-0.991319;0.051128;,
  -0.833477;-0.501520;0.231934;,
  -0.819265;0.500332;0.280128;,
  0.853234;0.308785;0.420291;,
  -0.056696;-0.841732;0.536910;,
  -0.057509;-0.049260;-0.997129;,
  -0.069969;-0.018571;-0.997376;,
  -0.059030;0.014330;-0.998153;,
  -0.083955;-0.987938;-0.130118;,
  0.347528;-0.933550;-0.087792;,
  0.505999;-0.858417;-0.084171;,
  -0.080551;0.711221;0.698339;,
  -0.369125;0.747082;0.552825;,
  -0.267392;0.704585;-0.657314;,
  -0.221336;0.630669;-0.743819;,
  -0.506433;0.738939;0.444404;,
  -0.586651;0.770866;0.248207;,
  0.061962;-0.997289;-0.039680;,
  -0.337460;-0.389674;0.856898;,
  0.230565;-0.214231;-0.949181;,
  -0.996771;0.059264;-0.054185;,
  -0.998431;0.017994;-0.053031;,
  -0.998386;-0.023306;-0.051786;,
  -0.203023;-0.202573;0.957991;,
  -0.098575;-0.293265;0.950936;,
  -0.843166;0.418836;0.337117;,
  -0.095961;-0.059597;-0.993599;,
  -0.078030;-0.089006;-0.992970;,
  -0.522537;0.852425;-0.018064;,
  -0.678183;0.734589;-0.021117;,
  -0.676823;0.735971;-0.016040;,
  -0.342270;0.939373;-0.020736;,
  0.724103;-0.653788;-0.219628;,
  0.642715;-0.712572;-0.281351;,
  0.523022;-0.836728;-0.162280;,
  0.568193;-0.812525;-0.130229;,
  -0.288141;0.940799;0.178530;,
  -0.058143;-0.007124;-0.998283;,
  -0.119050;0.986148;-0.115497;,
  -0.176311;0.983914;-0.028773;,
  0.149736;-0.985793;-0.076101;,
  -0.147400;0.975121;0.165566;,
  -0.217432;-0.974647;0.052792;,
  -0.035138;-0.051059;-0.998077;,
  -0.569310;-0.813146;0.121160;,
  -0.925517;-0.054304;-0.374791;,
  -0.104331;-0.992154;0.068880;,
  -0.101463;0.969223;0.224303;,
  -0.009270;0.958128;0.286190;,
  -0.029534;-0.980579;0.193890;,
  0.020376;0.004077;-0.999784;,
  -0.026143;0.010313;-0.999605;,
  -0.003857;0.002635;-0.999989;,
  0.024438;0.008076;-0.999669;,
  -0.073102;-0.011065;0.997263;,
  -0.070272;-0.008301;0.997493;,
  -0.013376;-0.937957;0.346493;,
  -0.629938;-0.775857;-0.034997;,
  -0.598751;-0.797113;-0.078160;,
  -0.659053;-0.752051;0.008281;,
  0.650951;-0.008766;-0.759069;,
  0.013679;-0.946163;-0.323402;,
  -0.063324;0.008038;-0.997961;,
  -0.203773;0.017732;-0.978858;,
  0.573168;0.706511;0.415115;,
  -0.060903;-0.009021;0.998103;,
  -0.058266;0.002725;0.998297;,
  -0.065717;0.007242;0.997812;,
  -0.135306;-0.013184;-0.990716;,
  -0.246114;0.017599;-0.969081;,
  -0.075825;0.019424;-0.996932;,
  0.221630;-0.910976;0.347854;,
  -0.082499;0.005860;0.996574;,
  -0.085202;0.003823;0.996356;,
  -0.716312;-0.697668;-0.012456;,
  -0.800816;-0.349524;0.486339;,
  -0.726251;0.686848;-0.028259;,
  -0.821336;0.366062;-0.437499;,
  -0.825400;0.503957;-0.254446;,
  -0.822179;0.399820;0.405175;,
  -0.792933;-0.358452;-0.492717;;
  168;
  3;0,1,0;,
  3;3,2,83;,
  3;6,5,4;,
  3;84,8,7;,
  3;4,9,6;,
  3;84,10,8;,
  3;5,10,4;,
  3;7,9,4;,
  3;13,12,11;,
  3;85,12,14;,
  3;17,16,15;,
  3;18,17,15;,
  3;20,19,17;,
  3;18,20,17;,
  3;14,6,9;,
  3;21,86,87;,
  3;88,21,87;,
  3;23,22,89;,
  3;90,23,89;,
  3;24,23,90;,
  3;91,24,90;,
  3;27,26,25;,
  3;30,29,28;,
  3;31,30,28;,
  3;33,32,92;,
  3;93,33,92;,
  3;31,28,94;,
  3;95,31,94;,
  3;34,31,95;,
  3;35,34,95;,
  3;96,33,93;,
  3;97,96,93;,
  3;36,27,98;,
  3;37,36,98;,
  3;13,26,27;,
  3;99,13,27;,
  3;100,30,31;,
  3;34,100,31;,
  3;101,102,102;,
  3;39,38,6;,
  3;36,14,12;,
  3;38,39,100;,
  3;34,38,100;,
  3;103,102,102;,
  3;104,105,40;,
  3;41,104,40;,
  3;83,106,3;,
  3;107,108,42;,
  3;43,107,42;,
  3;109,110,111;,
  3;112,109,111;,
  3;113,114,115;,
  3;116,113,115;,
  3;44,104,41;,
  3;45,44,41;,
  3;2,3,117;,
  3;118,107,43;,
  3;46,118,43;,
  3;119,109,112;,
  3;120,119,112;,
  3;121,116,115;,
  3;47,121,115;,
  3;48,44,45;,
  3;49,48,45;,
  3;50,117,122;,
  3;123,121,47;,
  3;51,123,47;,
  3;119,120,52;,
  3;124,118,46;,
  3;53,124,46;,
  3;51,89,22;,
  3;13,51,22;,
  3;0,125,0;,
  3;6,14,39;,
  3;38,54,5;,
  3;126,126,126;,
  3;36,37,39;,
  3;14,36,39;,
  3;35,53,54;,
  3;55,48,49;,
  3;56,55,49;,
  3;57,52,122;,
  3;54,53,52;,
  3;57,54,52;,
  3;38,34,35;,
  3;11,51,13;,
  3;127,123,51;,
  3;11,127,51;,
  3;8,55,56;,
  3;7,8,56;,
  3;128,57,129;,
  3;5,54,57;,
  3;10,5,57;,
  3;5,6,38;,
  3;85,11,12;,
  3;130,127,11;,
  3;9,130,11;,
  3;131,132,133;,
  3;134,131,133;,
  3;132,21,88;,
  3;133,132,88;,
  3;15,16,135;,
  3;136,15,135;,
  3;122,129,57;,
  3;129,8,10;,
  3;137,98,27;,
  3;138,139,138;,
  3;140,138,138;,
  3;25,137,27;,
  3;117,50,2;,
  3;122,52,50;,
  3;12,13,99;,
  3;54,38,35;,
  3;52,53,119;,
  3;60,59,58;,
  3;60,62,61;,
  3;65,64,63;,
  3;67,66,65;,
  3;69,68,60;,
  3;60,70,69;,
  3;72,141,71;,
  3;73,72,71;,
  3;142,74,65;,
  3;66,142,65;,
  3;61,72,143;,
  3;144,61,143;,
  3;61,70,60;,
  3;72,73,75;,
  3;78,71,61;,
  3;78,145,58;,
  3;58,62,60;,
  3;79,59,60;,
  3;80,146,147;,
  3;148,80,147;,
  3;68,69,5;,
  3;10,68,5;,
  3;75,74,142;,
  3;149,150,151;,
  3;5,149,6;,
  3;152,74,75;,
  3;76,152,75;,
  3;67,81,9;,
  3;6,67,9;,
  3;81,63,130;,
  3;9,81,130;,
  3;58,77,78;,
  3;61,62,78;,
  3;58,80,76;,
  3;77,58,76;,
  3;74,152,64;,
  3;65,74,64;,
  3;63,81,65;,
  3;153,154,148;,
  3;147,153,148;,
  3;60,68,79;,
  3;150,149,144;,
  3;143,150,144;,
  3;65,81,67;,
  3;79,68,10;,
  3;8,79,10;,
  3;155,156,82;,
  3;157,158,159;,
  3;159,160,157;,
  3;82,161,155;,
  3;156,160,82;,
  3;158,161,159;,
  3;154,153,8;,
  3;7,154,8;;
 }
 MeshTextureCoords {
  143;
  0.678200;0.980500;,
  0.740200;0.980000;,
  0.750000;0.995100;,
  0.674300;0.950700;,
  0.744100;0.956100;,
  0.837000;0.955700;,
  0.837200;0.972900;,
  0.814600;0.966300;,
  0.837400;0.972900;,
  0.837200;0.957000;,
  0.837100;0.953100;,
  0.837300;0.979500;,
  0.958600;0.868700;,
  0.930500;0.802000;,
  0.912700;0.803700;,
  0.916100;0.752300;,
  0.950000;0.807800;,
  0.747700;0.956100;,
  0.748800;0.912900;,
  0.751700;0.908900;,
  0.751900;0.955700;,
  0.752000;0.983100;,
  0.746100;0.996700;,
  0.954500;0.751500;,
  0.750800;0.958900;,
  0.962900;0.951200;,
  0.961500;0.911700;,
  0.940200;0.910000;,
  0.941400;0.953500;,
  0.963100;0.987100;,
  0.943100;0.984900;,
  0.975800;0.889100;,
  0.965600;0.893000;,
  0.977800;0.938700;,
  0.856600;0.886200;,
  0.827500;0.959600;,
  0.824300;0.934900;,
  0.832600;0.879500;,
  0.806900;0.871100;,
  0.801300;0.926300;,
  0.785800;0.944000;,
  0.785200;0.892400;,
  0.837400;0.818800;,
  0.812000;0.820300;,
  0.795100;0.867200;,
  0.968800;0.855500;,
  0.992700;0.888100;,
  0.992900;0.850600;,
  0.859400;0.817100;,
  0.856400;0.782700;,
  0.835000;0.782200;,
  0.828100;0.748900;,
  0.662800;0.994100;,
  0.662000;0.946700;,
  0.787000;0.951700;,
  0.785200;0.996100;,
  0.775400;0.983000;,
  0.775300;0.955700;,
  0.882800;0.986500;,
  0.933300;0.987500;,
  0.934100;0.954800;,
  0.879600;0.952300;,
  0.673600;0.909200;,
  0.662200;0.908800;,
  0.786900;0.912600;,
  0.777100;0.909100;,
  0.874800;0.909600;,
  0.933300;0.910900;,
  0.665000;0.862300;,
  0.659200;0.861800;,
  0.745300;0.909400;,
  0.869900;0.856000;,
  0.933900;0.864700;,
  0.748700;0.873400;,
  0.784200;0.862700;,
  0.974000;0.797600;,
  0.785600;0.803000;,
  0.784300;0.749200;,
  0.665000;0.801800;,
  0.658200;0.801800;,
  0.738500;0.802900;,
  0.872000;0.804600;,
  0.673800;0.747600;,
  0.658700;0.747600;,
  0.740800;0.749100;,
  0.876000;0.754100;,
  0.752100;0.878100;,
  0.751800;0.911500;,
  0.743700;0.956600;,
  0.747700;0.956100;,
  0.751700;0.908900;,
  0.751900;0.955700;,
  0.988400;0.937800;,
  0.441400;0.800800;,
  0.441400;0.863300;,
  0.390600;0.863300;,
  0.382800;0.800800;,
  0.375000;0.742200;,
  0.441400;0.992200;,
  0.441400;0.925800;,
  0.531300;0.925800;,
  0.531300;0.687500;,
  0.441400;0.687500;,
  0.441400;0.636700;,
  0.531300;0.742200;,
  0.531300;0.800800;,
  0.441400;0.742200;,
  0.375000;0.687500;,
  0.365300;0.742700;,
  0.367200;0.687500;,
  0.382800;0.636700;,
  0.375000;0.636700;,
  0.375000;0.800800;,
  0.531300;0.863300;,
  0.390600;0.925800;,
  0.539100;0.816400;,
  0.539100;0.753900;,
  0.625000;0.753900;,
  0.625000;0.816400;,
  0.539100;0.695300;,
  0.625000;0.695300;,
  0.382800;0.992200;,
  0.375000;0.992200;,
  0.382800;0.925800;,
  0.539100;0.632800;,
  0.625000;0.632800;,
  0.539100;0.992200;,
  0.539100;0.937500;,
  0.625000;0.937500;,
  0.625000;0.992200;,
  0.382800;0.863300;,
  0.531300;0.992200;,
  0.531300;0.636700;,
  0.539100;0.875000;,
  0.625000;0.875000;,
  0.025400;0.598400;,
  0.025100;0.588100;,
  0.006800;0.579600;,
  0.024900;0.574200;,
  0.025000;0.565600;,
  0.024900;0.580800;,
  0.025600;0.615600;,
  0.025000;0.555200;;
 }
}
