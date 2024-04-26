//uniform sampler2D qt_Texture0;

//varying highp vec4 qt_TexCoord0;
uniform vec2 iResolution;
uniform float iTime;
const float MAX_DIST = 100000.0;
uniform vec3 iRotate;
uniform vec3 iCameraPos;
//uniform float iSensitivity;
uniform float iZoom;

mat2 rot (float a) {
  float s = sin(a);
  float c = cos(a);
  return mat2 (c, -s, s, c);
}

vec2 sphereIntersect( in vec3 ro, in vec3 rd, float ra )
{
    float b = dot( ro, rd );
	float c = dot( ro, ro ) - ra*ra;
	float h = b*b - c;
	if( h<0.0 ) return vec2(-1.0); // no intersection
	h = sqrt( h );
	return vec2( -b-h, -b+h );
}

vec2 boxIntersect( in vec3 ro, in vec3 rd, vec3 rad, out vec3 outNormal )
{
    vec3 m = 1.0/rd; // can precompute if traversing a set of aligned boxes
	vec3 n = m*ro;   // can precompute if traversing a set of aligned boxes
	vec3 k = abs(m)*rad;
	vec3 t1 = -n - k;
	vec3 t2 = -n + k;
	float tN = max( max( t1.x, t1.y ), t1.z );
	float tF = min( min( t2.x, t2.y ), t2.z );
	if( tN>tF || tF<0.0) return vec2(-1.0); // no intersection
	outNormal = -sign(rd) * step(t1.yzx, t1.xyz) * step(t1.zxy, t1.xyz);
	//outNormal = (tN>0.0) ? step(vec3(tN),t1)) : // ro ouside the box
	//                       step(t2,vec3(tF)));  // ro inside the box
	//outNormal *= -sign(rd);
	return vec2( tN, tF );
}

float plaIntersect( in vec3 ro, in vec3 rd, in vec4 p )
{
    return -(dot(ro,p.xyz)+p.w)/dot(rd,p.xyz);
}

vec3 castRay(vec3 ro, vec3 rd){
  vec2 minIt = vec2(MAX_DIST);
  vec2 it;
  vec3 n;
  vec3 spherePosition = vec3(-1.0, 0.0, 5.0);
  it = sphereIntersect(ro - spherePosition, rd, 1.0);
  if(it.x > 0.0 && it.x < minIt.x){
	minIt =it;
	vec3 itPos = ro + rd * it.x;
	n = itPos - spherePosition;
  }
  vec3 boxN;
  vec3 boxPosition = vec3 (2.0, 0.0, 5.0);
  it = boxIntersect(ro- boxPosition, rd, vec3(1.0), boxN);
  if(it.x > 0.0 && it.x < minIt.x){
	minIt =it;
	n = boxN;
  }
  vec3 planeN = vec3(0.0,1.0, 0.0);
  it.x = plaIntersect(ro, rd, vec4(planeN, 1.0));
  if(it.x > 0.0 && it.x < minIt.x){
	minIt =it;
	n = planeN;
  }
  if (minIt.x >= MAX_DIST) return vec3(135.0/255.0, 206.0/255.0, 235.0/255.0);

//  vec2 it = sphereIntersect(ro, rd, 1.0);
//  if (it.x < 0.0) return vec3(0.0);
//  vec3 itPos = ro + rd * it.x;
//  vec3 n = itPos;
  vec3 light = normalize( vec3 (cos(iTime/7.0), abs(sin(iTime/11.0)), sin(iTime/15.0)));
  float diffuse = max(0.0, dot(light, n)) * 0.5;
  //vec3 reflected = reflect(rd,n);
 float spectr = pow(max(0.0, dot(reflect(rd,n), light)), 16.0);
 return vec3(diffuse) + vec3(spectr);
}

void main(void) {

  vec2 uv = ((gl_FragCoord.xy / iResolution.xy) - 0.5) * iResolution / iResolution.y;
  //uv += 0.5;
  vec3 rayOrigin = iCameraPos;
  //rayOrigin.yz *= rot(-iRotate.x); //вокруг Х
  //rayOrigin.xz *= rot(iRotate.y); //вокруг У
  vec3 rayDirection = normalize(vec3(uv, iZoom));
  //iRotate.xy /= iResolution.xy;
  rayDirection.yz *= rot(-iRotate.x); //вокруг Х
  rayDirection.xz *= rot(iRotate.y); //вокруг У
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
