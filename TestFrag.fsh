//uniform sampler2D qt_Texture0;

//varying highp vec4 qt_TexCoord0;
uniform vec2 iResolution;
uniform float iTime;

vec2 sphereIntersect( in vec3 ro, in vec3 rd, float ra )
{
    float b = dot( ro, rd );
	float c = dot( ro, ro ) - ra*ra;
	float h = b*b - c;
	if( h<0.0 ) return vec2(-1.0); // no intersection
	h = sqrt( h );
	return vec2( -b-h, -b+h );
}

vec3 castRay(vec3 ro, vec3 rd){
  vec2 it = sphereIntersect(ro, rd, 1.0);
  if (it.x < 0.0) return vec3(0.0);
  vec3 itPos = ro + rd * it.x;
  vec3 n = itPos;
  vec3 light = normalize( vec3 (cos(iTime), sin(iTime/5), sin(iTime)));
  float diffuse = max(0.0, dot(light, n)) * 0.5;
  vec3 reflected = reflect(rd,n);
  float spectr = pow(max(0.0, dot(reflected, light)), 16.0);
  return vec3(diffuse) + vec3(spectr);
}

void main(void) {
  vec2 uv = ((gl_FragCoord.xy / iResolution.xy) - 0.5) * iResolution / iResolution.y;
  //uv += 0.5;
  vec3 rayOrigin = vec3(0.0, 0.0,-5.0);
  vec3 rayDirection = normalize(vec3(uv, 1.0));
  vec3 col = castRay(rayOrigin, rayDirection);
  gl_FragColor = vec4(col, 1.0);
  //vec3 uvxyx = vec3(uv, uv.x);
  //vec3 iTime3 = vec3(iTime);
  //vec3 col = 0.5 + 0.5*cos(iTime3+uvxyx+vec3(0,2,4));
  //vec3 col = vec3(uv.xy, 0.0);
  //gl_FragColor = vec4(col,1.0);
  //uv.x *= iResolution.x / iResolution.y; //aspect fix

  //gl_FragColor = vec4(uv, 0.0, 1.0);
  //uv = uv * 2.0 - 1.0; //transform from [0,1] to [-1,1]
}
