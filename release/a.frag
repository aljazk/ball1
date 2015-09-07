uniform vec2 mousePos;
uniform float lightDistance;
uniform float lightResize;
uniform float lightSpeed;
uniform vec3 lightColor;
uniform float time;

void main (void) 
{ 
    float dist = sqrt(pow(mousePos.x-gl_FragCoord.x, 2)+pow(mousePos.y-gl_FragCoord.y, 2));
	dist += abs(sin(time/lightSpeed)*lightResize);
	lightColor.r -= (dist/lightDistance);
	lightColor.g -= (dist/lightDistance);
	lightColor.b -= (dist/lightDistance);
	gl_FragColor = vec4(lightColor, 1);
}