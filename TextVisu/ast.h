/*
** "THE BEER-WARE LICENSE" (Revision 42):
** <simon.mikuda@gmail.com> wrote this file. As long as you retain this notice you
** can do whatever you want with this stuff. If we meet some day, and you think
** this stuff is worth it, you can buy me a beer in return.
*/

#pragma once

void ast1()
{
  TextE elem1(1000, " Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.");
  TextE elem2(1000, "Integer quam nisl, congue id eleifend quis, bibendum in mauris. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan lacinia nisl, vel sodales magna dignissim eget.");
  TextE elem3(1000, "Nullam accumsan lacinia nisl, vel sodales magna dignissim eget.");
  
  TextE elem4(1000, "Integer quam nisl, congue id eleifend quis, bibendum in mauris. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan lacinia nisl, vel sodales magna dignissim eget. Ut tempor ante non justo iaculis elementum. Vivamus sed dui massa, ut mattis ante. Praesent ultricies purus vel lorem congue eget blandit elit vulputate. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus gravida feugiat facilisis. Curabitur commodo tincidunt ullamcorper. Mauris vitae leo eros. Donec ullamcorper fermentum placerat. Etiam in interdum urna. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.");
  TextE elem5(2000, "Integer quam nisl, congue id eleifend quis, bibendum in mauris. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan lacinia nisl, vel sodales magna dignissim eget. Ut tempor ante non justo iaculis elementum. Vivamus sed dui massa, ut mattis ante. Praesent ultricies purus vel lorem congue eget blandit elit vulputate. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus gravida feugiat facilisis. Curabitur commodo tincidunt ullamcorper. Mauris vitae leo eros. Donec ullamcorper fermentum placerat. Etiam in interdum urna. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.");
  TextE elem6(4000, "Integer quam nisl, congue id eleifend quis, bibendum in mauris. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan lacinia nisl, vel sodales magna dignissim eget. Ut tempor ante non justo iaculis elementum. Vivamus sed dui massa, ut mattis ante. Praesent ultricies purus vel lorem congue eget blandit elit vulputate. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus gravida feugiat facilisis. Curabitur commodo tincidunt ullamcorper. Mauris vitae leo eros. Donec ullamcorper fermentum placerat. Etiam in interdum urna. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.");
  
  HorizontalC com1;
  HorizontalC com2;
  VerticalC ver1;
  VerticalC ver2;
  VerticalC ver3;
  HorizontalC mainComponent;

  com1.add(elem1).add(elem2).add(elem3);
  ver1.add(com1).add(elem6);
  ver3.add(elem6).add(ver1).add(elem4);
  com2.add(elem2).add(ver3).add(com1);
  ver2.add(elem5).add(com2);
  mainComponent.add(elem4).add(ver2).add(elem1).add(elem4).add(ver3).add(elem5).add(ver1).add(com1).add(com2);

  root = &mainComponent;
  glutMainLoop();
}

void ast2()
{
  TextE elem1(3000, " Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.");
  TextE elem2(3000, "Integer quam nisl, congue id eleifend quis, bibendum in mauris. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan lacinia nisl, vel sodales magna dignissim eget.");
  TextE elem3(3000, "Nullam accumsan lacinia nisl, vel sodales magna dignissim eget.");
  
  VerticalC ver1;
  VerticalC mainComponent;

  ver1.add(elem1).add(elem2).add(elem3);
  mainComponent
  	.add(ver1).add(elem1).add(elem2).add(elem3)
  	.add(ver1).add(elem1).add(elem2).add(elem3)
  	.add(ver1).add(elem1).add(elem2).add(elem3);
  
  root = &mainComponent;
  glutMainLoop();
}

void ast3()
{
  TextE elem1(1000, " Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.");
  TextE elem2(1500, "Integer quam nisl, congue id eleifend quis, bibendum in mauris. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam accumsan lacinia nisl, vel sodales magna dignissim eget.");
  TextE elem3(1000, "Nullam accumsan lacinia nisl, vel sodales magna dignissim eget.");
  
  HorizontalC ver1, ver2;
  HorizontalC mainComponent;

  ver1.add(elem1).add(elem2).add(elem3);
  ver2
  	.add(ver1).add(elem1).add(elem2).add(elem3)
  	.add(ver1).add(elem1).add(elem2).add(elem3)
  	.add(ver1).add(elem1).add(elem2).add(elem3);

  mainComponent.add(elem1).add(elem2).add(elem3).add(ver2).add(ver1);
  
  root = &mainComponent;
  glutMainLoop();
}