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
 110;
 -0.76257;11.10321;1.16799;,
 -1.06824;11.79519;2.41419;,
 1.07148;11.09988;1.15119;,
 -1.98528;11.58693;0.49953;,
 1.52160;11.79519;2.39067;,
 2.39829;11.58693;0.23082;,
 -1.41756;4.98639;-2.54376;,
 -1.63593;3.92493;-4.04862;,
 -2.43201;0.71703;-3.08793;,
 -2.38497;0.71703;-0.68958;,
 -2.27079;0.16281;-0.45444;,
 2.37477;0.16281;-0.49473;,
 1.73655;0.16281;3.70743;,
 -1.22274;0.16281;3.73092;,
 -2.43201;0.16281;-3.05769;,
 2.34789;0.16281;-3.10137;,
 2.51586;0.71703;-0.73323;,
 -2.38497;0.71703;-0.68958;,
 2.57631;4.11303;0.86901;,
 2.37477;6.52146;0.86901;,
 1.68615;6.86412;3.46557;,
 1.55517;4.98639;-2.57061;,
 1.57530;6.44421;-1.75101;,
 -2.17674;6.52146;1.05042;,
 -1.07160;6.44421;-1.72752;,
 -1.13208;6.86412;3.48909;,
 -2.51934;4.11303;1.06383;,
 -2.56638;6.95478;1.18479;,
 -1.27650;7.33773;3.82833;,
 -1.22613;11.70786;2.86767;,
 -2.26071;11.52309;0.62382;,
 1.78695;6.92121;-2.07684;,
 -1.25298;6.92121;-2.05335;,
 -1.27314;11.45256;-2.42955;,
 1.64250;11.45256;-2.45307;,
 1.79028;7.33773;3.80148;,
 1.52493;11.77170;2.86767;,
 -1.94829;2.92392;-6.38316;,
 1.52493;3.92493;-4.07547;,
 -2.44545;0.71703;1.02690;,
 -2.38497;0.71703;-0.68958;,
 -2.27079;0.16281;-0.45444;,
 -2.43201;0.71703;-3.08793;,
 -2.43201;0.16281;-3.05769;,
 2.86854;6.95478;0.95637;,
 2.37477;6.52146;0.86901;,
 1.57530;6.44421;-1.75101;,
 2.86854;6.95478;0.95637;,
 1.68615;6.86412;3.46557;,
 2.37477;6.52146;0.86901;,
 2.49570;0.71703;-6.16146;,
 2.34789;0.71703;-3.12825;,
 2.34789;0.16281;-3.10137;,
 2.49570;0.16281;-6.17490;,
 1.80039;2.92392;-6.41673;,
 2.34789;0.71703;-3.12825;,
 2.49570;0.71703;-6.16146;,
 2.71068;0.71703;0.98322;,
 1.94481;0.71703;3.72423;,
 1.73655;0.16281;3.70743;,
 0.94047;1.95990;-9.99078;,
 1.34019;0.71703;-9.66828;,
 -0.29901;0.71703;-10.46775;,
 -1.30674;1.95990;-9.97062;,
 -1.83411;0.16281;-9.63471;,
 1.47456;0.16281;-9.66495;,
 2.49570;0.16281;-6.17490;,
 -2.89890;0.16281;-6.12786;,
 -0.29901;0.16281;-10.47780;,
 2.37477;0.16281;-0.49473;,
 1.47456;0.16281;-9.66495;,
 1.34019;0.71703;-9.66828;,
 -0.29901;0.16281;-10.47780;,
 -0.29901;0.71703;-10.46775;,
 -1.42095;3.97869;3.86865;,
 -2.44545;0.71703;1.02690;,
 -1.41756;0.71703;3.75447;,
 2.51586;0.71703;-0.73323;,
 1.93137;3.97869;3.83844;,
 0.27873;6.86412;3.64362;,
 0.25860;3.97869;4.23816;,
 -2.17674;6.52146;1.05042;,
 -1.13208;6.86412;3.48909;,
 1.94481;0.71703;3.72423;,
 0.26865;0.71703;4.12059;,
 2.51586;0.71703;-0.73323;,
 2.71068;0.71703;0.98322;,
 -1.22274;0.16281;3.73092;,
 -1.69977;0.71703;-9.64143;,
 -2.89890;0.71703;-6.11442;,
 -1.41756;0.71703;3.75447;,
 -2.89890;0.71703;-6.11442;,
 -2.89890;0.16281;-6.12786;,
 0.27873;6.86412;3.64362;,
 -1.83411;0.16281;-9.63471;,
 -1.69977;0.71703;-9.64143;,
 0.26865;0.71703;4.12059;,
 -1.07160;6.44421;-1.72752;,
 1.48128;11.51640;-2.19777;,
 2.39829;11.58693;0.23082;,
 2.67372;11.52309;0.30471;,
 2.39829;11.58693;0.23082;,
 1.52160;11.79519;2.39067;,
 2.67372;11.52309;0.30471;,
 -1.10853;11.51640;-2.17428;,
 -1.98528;11.58693;0.49953;,
 -1.06824;11.79519;2.41419;,
 0.26865;0.71703;4.12059;,
 0.25860;3.97869;4.23816;,
 0.27873;6.86412;3.64362;;
 
 122;
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
 3;27,28,29;,
 3;30,27,29;,
 3;31,32,33;,
 3;34,31,33;,
 3;28,35,36;,
 3;29,28,36;,
 3;37,7,38;,
 3;7,6,21;,
 3;39,40,41;,
 3;21,38,7;,
 3;32,27,30;,
 3;33,32,30;,
 3;40,42,43;,
 3;31,44,45;,
 3;46,31,45;,
 3;47,35,48;,
 3;49,47,48;,
 3;50,51,52;,
 3;53,50,52;,
 3;54,38,55;,
 3;56,54,55;,
 3;57,58,59;,
 3;60,54,56;,
 3;61,60,56;,
 3;62,60,61;,
 3;37,54,60;,
 3;63,37,60;,
 3;62,63,60;,
 3;64,65,66;,
 3;67,64,66;,
 3;64,68,65;,
 3;59,69,57;,
 3;53,70,71;,
 3;50,53,71;,
 3;70,72,73;,
 3;71,70,73;,
 3;74,26,75;,
 3;76,74,75;,
 3;52,51,77;,
 3;21,6,24;,
 3;22,21,24;,
 3;19,18,21;,
 3;20,78,18;,
 3;78,20,79;,
 3;80,78,79;,
 3;28,27,81;,
 3;82,28,81;,
 3;6,26,23;,
 3;83,78,80;,
 3;84,83,80;,
 3;69,77,57;,
 3;38,21,85;,
 3;55,38,85;,
 3;85,21,18;,
 3;86,85,18;,
 3;18,78,83;,
 3;86,18,83;,
 3;41,87,39;,
 3;88,63,62;,
 3;37,63,88;,
 3;89,37,88;,
 3;87,90,39;,
 3;7,37,89;,
 3;8,7,89;,
 3;15,14,67;,
 3;66,15,67;,
 3;42,91,92;,
 3;43,42,92;,
 3;28,82,93;,
 3;38,54,37;,
 3;26,74,25;,
 3;94,92,91;,
 3;95,94,91;,
 3;72,94,95;,
 3;73,72,95;,
 3;9,75,26;,
 3;6,9,26;,
 3;96,90,87;,
 3;32,31,46;,
 3;97,32,46;,
 3;27,32,97;,
 3;81,27,97;,
 3;98,99,100;,
 3;34,98,100;,
 3;101,102,36;,
 3;103,101,36;,
 3;35,47,103;,
 3;36,35,103;,
 3;44,31,34;,
 3;100,44,34;,
 3;104,98,34;,
 3;33,104,34;,
 3;105,104,33;,
 3;30,105,33;,
 3;106,105,30;,
 3;29,106,30;,
 3;102,106,29;,
 3;36,102,29;,
 3;74,76,107;,
 3;108,74,107;,
 3;25,74,108;,
 3;109,25,108;,
 3;59,58,96;,
 3;96,87,59;,
 3;93,48,35;,
 3;35,28,93;;
 
 MeshMaterialList {
  9;
  122;
  4,
  4,
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
  0,
  4,
  4,
  4,
  4,
  4,
  4,
  0,
  0,
  0,
  0,
  4,
  4,
  0,
  4,
  4,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  4;;
  Material {
   0.800000;0.677600;0.627200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.564800;0.800000;0.380000;1.000000;;
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
   0.339200;0.339200;0.339200;1.000000;;
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
   0.800000;0.084800;0.232000;1.000000;;
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
  105;
  0.158005;0.974494;-0.159364;,
  0.084771;0.991840;-0.095223;,
  -0.173495;0.884893;-0.432277;,
  0.255804;0.870443;-0.420588;,
  -0.009948;0.982322;-0.186935;,
  -0.076322;0.977588;-0.196205;,
  -0.059463;0.988100;-0.141857;,
  -0.040841;0.993685;-0.104511;,
  -0.988953;0.125959;0.078140;,
  -0.952578;0.303171;0.026125;,
  -0.958220;0.222795;-0.179381;,
  -0.997966;0.019019;-0.060848;,
  0.202148;-0.943545;0.262410;,
  0.637334;-0.770587;-0.000688;,
  -0.251799;-0.965723;0.063053;,
  -0.476190;-0.784364;0.397512;,
  0.002055;-0.973709;0.227786;,
  0.000698;-0.997080;0.076359;,
  0.001378;-0.988264;0.152753;,
  0.915429;-0.271723;0.296910;,
  0.943272;-0.317283;-0.097826;,
  0.996748;0.066888;0.044937;,
  0.939103;-0.198209;-0.280713;,
  0.963157;0.125057;-0.238094;,
  -0.896218;-0.266259;-0.354822;,
  -0.994182;-0.103951;-0.028218;,
  -0.992230;0.080774;0.094633;,
  -0.609395;-0.099654;0.786579;,
  -0.902880;0.107189;0.416315;,
  -0.548726;-0.472731;0.689511;,
  -0.951812;-0.302651;0.049570;,
  -0.994582;0.034622;-0.098019;,
  -0.007870;-0.082882;-0.996528;,
  -0.231216;-0.490166;-0.840402;,
  -0.007598;-0.249903;-0.968241;,
  -0.008039;-0.082995;-0.996518;,
  0.001791;0.210665;0.977557;,
  0.041932;-0.256838;0.965544;,
  -0.003940;0.889597;-0.456729;,
  -0.002889;0.944824;-0.327565;,
  -0.952670;-0.226459;0.202822;,
  0.937519;-0.347760;0.010970;,
  0.987366;0.158288;-0.007311;,
  0.982167;0.134904;-0.130951;,
  0.979960;0.078670;-0.183001;,
  0.958385;0.273976;-0.080216;,
  0.963171;-0.102791;0.248467;,
  0.959482;-0.268149;0.086545;,
  0.668111;0.219873;-0.710833;,
  0.804470;0.100443;-0.585440;,
  0.049549;0.063135;-0.996774;,
  -0.471643;0.484441;-0.736797;,
  0.000000;-1.000000;0.000000;,
  -0.649969;0.034314;0.759186;,
  -0.642116;-0.139761;0.753760;,
  0.975309;0.053552;0.214253;,
  0.048306;-0.179201;0.982626;,
  0.026806;0.075672;0.996772;,
  -0.030011;-0.160329;0.986607;,
  -0.767800;0.154772;-0.621714;,
  -0.970385;0.213770;-0.112497;,
  0.232601;0.969686;-0.074870;,
  0.002029;-0.973697;0.227839;,
  -0.008083;-0.392734;-0.919617;,
  -0.007979;-0.391953;-0.919951;,
  -0.008188;-0.393514;-0.919282;,
  -0.004983;0.214750;0.976656;,
  -0.004502;0.855477;-0.517821;,
  -0.006703;0.670258;-0.742098;,
  -0.006589;0.670199;-0.742152;,
  -0.975868;-0.215636;-0.034385;,
  -0.939752;-0.006952;-0.341788;,
  -0.951251;-0.029718;-0.306982;,
  -0.996357;0.004647;0.085159;,
  0.855330;-0.434657;-0.281927;,
  0.920896;-0.074590;0.382605;,
  0.999960;-0.000734;0.008930;,
  0.974564;0.214394;-0.065272;,
  0.903245;-0.347064;0.252377;,
  -0.002933;0.944845;-0.327506;,
  -0.002329;0.965633;-0.259900;,
  0.647398;0.123815;-0.752028;,
  -0.210690;0.050834;-0.976230;,
  0.991039;0.040581;-0.127262;,
  -0.007804;0.490041;-0.871665;,
  -0.007735;0.490135;-0.871612;,
  0.196032;0.100418;0.975442;,
  0.121708;-0.244205;0.962056;,
  -0.616771;-0.678394;0.399219;,
  0.230459;-0.060922;0.971173;,
  -0.924729;0.327145;-0.194557;,
  -0.999983;0.003937;0.004184;,
  -0.841734;0.118662;-0.526691;,
  -0.210766;-0.115336;0.970709;,
  -0.006854;-0.564017;-0.825735;,
  -0.007316;-0.565929;-0.824421;,
  0.071371;0.977492;-0.198534;,
  0.179913;0.983111;0.033523;,
  0.987555;0.076757;0.137273;,
  0.908780;0.137367;0.394016;,
  0.939341;-0.003922;-0.342962;,
  -0.166897;0.974289;-0.151350;,
  -0.273347;0.961832;-0.012656;,
  -0.115610;0.987791;0.104419;,
  0.228591;-0.115201;0.966683;;
  122;
  3;3,4,2;,
  3;6,4,3;,
  3;4,7,2;,
  3;2,7,1;,
  3;10,9,8;,
  3;11,10,8;,
  3;14,13,12;,
  3;15,14,12;,
  3;18,17,16;,
  3;62,18,16;,
  3;63,64,63;,
  3;65,63,63;,
  3;21,20,19;,
  3;23,22,20;,
  3;25,24,10;,
  3;27,25,26;,
  3;30,29,28;,
  3;31,30,28;,
  3;34,33,32;,
  3;35,34,32;,
  3;36,37,36;,
  3;66,36,36;,
  3;39,67,38;,
  3;67,68,69;,
  3;40,11,70;,
  3;69,38,67;,
  3;71,30,31;,
  3;72,71,31;,
  3;11,8,73;,
  3;74,41,20;,
  3;22,74,20;,
  3;41,75,19;,
  3;20,41,19;,
  3;43,42,76;,
  3;44,43,76;,
  3;45,77,42;,
  3;43,45,42;,
  3;47,46,78;,
  3;48,45,43;,
  3;49,48,43;,
  3;50,48,49;,
  3;39,79,80;,
  3;51,39,80;,
  3;50,51,48;,
  3;52,52,52;,
  3;52,52,52;,
  3;52,52,52;,
  3;12,13,47;,
  3;44,81,49;,
  3;43,44,49;,
  3;81,82,50;,
  3;49,81,50;,
  3;53,26,40;,
  3;54,53,40;,
  3;76,42,83;,
  3;69,68,84;,
  3;85,69,84;,
  3;20,21,23;,
  3;19,55,21;,
  3;86,87,56;,
  3;57,86,56;,
  3;29,30,88;,
  3;27,29,25;,
  3;10,26,25;,
  3;89,86,57;,
  3;58,89,57;,
  3;13,83,47;,
  3;77,23,83;,
  3;42,77,83;,
  3;83,23,21;,
  3;47,83,21;,
  3;21,55,46;,
  3;47,21,46;,
  3;14,15,40;,
  3;59,51,50;,
  3;90,51,59;,
  3;60,90,59;,
  3;15,54,40;,
  3;9,90,60;,
  3;8,9,60;,
  3;17,18,52;,
  3;52,17,52;,
  3;8,60,91;,
  3;73,8,91;,
  3;29,27,56;,
  3;38,79,39;,
  3;26,53,27;,
  3;92,91,60;,
  3;59,92,60;,
  3;82,92,59;,
  3;50,82,59;,
  3;11,40,26;,
  3;10,11,26;,
  3;58,54,93;,
  3;33,34,94;,
  3;95,33,94;,
  3;30,33,24;,
  3;25,30,24;,
  3;0,1,61;,
  3;96,0,61;,
  3;1,7,97;,
  3;61,1,97;,
  3;75,41,98;,
  3;99,75,98;,
  3;41,74,100;,
  3;98,41,100;,
  3;5,0,96;,
  3;101,5,96;,
  3;6,5,101;,
  3;102,6,101;,
  3;4,6,102;,
  3;103,4,102;,
  3;7,4,103;,
  3;97,7,103;,
  3;53,54,58;,
  3;57,53,58;,
  3;27,53,57;,
  3;56,27,57;,
  3;104,89,58;,
  3;58,15,12;,
  3;56,87,37;,
  3;37,29,56;;
 }
 MeshTextureCoords {
  110;
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
  0.824600;0.610200;,
  0.878900;0.610200;,
  0.878900;0.734800;,
  0.824200;0.734800;,
  0.701000;0.610200;,
  0.768200;0.610200;,
  0.768200;0.734800;,
  0.701200;0.734800;,
  0.939100;0.610200;,
  0.939700;0.734800;,
  0.827300;0.442200;,
  0.768900;0.496700;,
  0.976600;0.529500;,
  0.976600;0.503000;,
  0.990900;0.506600;,
  0.976800;0.465900;,
  0.991000;0.466400;,
  0.648400;0.610400;,
  0.648900;0.595500;,
  0.701000;0.595500;,
  0.994500;0.610200;,
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
  0.768400;0.595300;,
  0.701600;0.744100;,
  0.647700;0.744100;,
  0.648000;0.734800;,
  0.994800;0.744500;,
  0.940200;0.744500;,
  0.993900;0.734800;,
  0.768200;0.743900;,
  0.824200;0.744500;,
  0.878900;0.744400;,
  0.963700;0.460900;,
  0.963200;0.527900;,
  0.962600;0.593200;;
 }
}
