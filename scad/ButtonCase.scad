include <BOSL/shapes.scad>


$fn=90;
wt=3.3;
module esp32() {
    color("green") translate([-100,-118.5,0])import("/home/dgs/Downloads/lora32&kit32_all.stl",convexity = 10);
}

module case(h=30) {
    difference() {
        union(){
            difference(){
                cuboid([68,68,h],fillet=8.5,edges=EDGE_FR_RT+EDGE_FR_LF+EDGE_BK_RT+EDGE_BK_LF);
                translate([0,0,1.65])cuboid([68-wt,68-wt,h],fillet=8.5,edges=EDGE_FR_RT+EDGE_FR_LF+EDGE_BK_RT+EDGE_BK_LF);
            }
            translate([25.75,25.75,-(h/2)]) cylinder(h=h,d=6);
            translate([-25.75,-25.75,-(h/2)])cylinder(h=h,d=6);
            translate([25.75,-25.75,-(h/2)])cylinder(h=h,d=6);
            translate([-25.75,25.75,-(h/2)])cylinder(h=h,d=6);
            translate([-32,0,0]) sparse_strut(h=h, strut=2,l=70-wt*4, thick=3);
            translate([0,32,0]) rotate([0,0,90]) sparse_strut(h=h, strut=2,l=70-wt*4, thick=3);
            translate([0,-32,0]) rotate([0,0,90]) sparse_strut(h=h, strut=2,l=70-wt*4, thick=3);
        }
        
        translate([25.75,25.75,-(h/2)]) cylinder(h=h+1,d=4);
        translate([-25.75,-25.75,-(h/2)])cylinder(h=h+1,d=4);
        translate([25.75,-25.75,-(h/2)])cylinder(h=h+1,d=4);
        translate([-25.75,25.75,-(h/2)]) cylinder(h=h+1,d=4);

        translate([33,0,6]) cuboid([5,20.5,33.5]);
        translate([30,0,-h/2]) cuboid([5,10,5]);
    }

}
module switchBody() {
    cuboid([30,30,25]);
}

module lipo() {
    cuboid([42,25,10.5]);
}
//translate([27.5,0,6.1]) rotate([0,90,0]) esp32();
//lipo();
case(h=55);