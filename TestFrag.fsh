//uniform sampler2D qt_Texture0;

//varying highp vec4 qt_TexCoord0;
uniform vec2 iResolution;
uniform float iTime;

void main(void) {
  vec2 uv = gl_FragCoord.xy/iResolution.xy;
  vec3 uvxyx = vec3(uv, uv.x);
  vec3 iTime3 = vec3(iTime);
  vec3 col = 0.5 + 0.5*cos(iTime3+uvxyx+vec3(0,2,4));
  gl_FragColor = vec4(col,1.0);
  //uv.x *= iResolution.x / iResolution.y; //aspect fix

  //gl_FragColor = vec4(uv, 0.0, 1.0);
  //uv = uv * 2.0 - 1.0; //transform from [0,1] to [-1,1]
}
