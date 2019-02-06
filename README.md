# Got Your Back
Our Sibb family's MakeHarvard 2019 Project. Check out our [devpost](https://devpost.com/software/gotyourback-x30znu) for photos of the final project, and look at the subfolders for code examples.

# Our Vision
Everyone has been scared of walking home alone at night or trying to navigate somewhere unfamiliar. The minute you pay too much attention to your phone, you suddenly look vulnerable, yet phones are essential for navigation. For people with auditory and visual impairments, this is even more concerning as it can be harder to detect people around while also navigating different terrain. Thus, we created GotYourBack.

GotYourBack is a backpack that subtly informs users of a variety of different surrounding stimuli by using vibration on the user's shoulder to help guide them home and alert them of possible danger. Not only does it give a non-obvious way to notify a user which direction to turn when reaching a junction, but it actively detects people coming from behind the user. If they get too close, it will buzz a notification to you as well as scare off the person with a loud screech.

# What it does
GotYourBack allows hands-free navigation in an accessible manner while keeping the wearer informed of events around them. GotYourBack communicates with Google in order to determine the different steps needed to reach their target destination. Any Android device can use our app and connect via Bluetooth to our Arduino. This allows for navigation with subtle vibration prompts while wearing our GotYourBack(pack).

# Key Technologies
Our key components are an Ardunio-Uno based hardware device (more specifically, a plywood and composite casing with external vibration motors that connect to the straps of any backpack) where each component is mounted that fits in a backpack and communicates via Bluetooth to an Android app (in our case, on a Kindle fire phone fit with Android features) that leverages the Google maps API to provide navigational assistance. We used the Arduino to command all of the electrical components of our project and with the potential to communicate over Bluetooth to the Amazon Fire Phone. The Amazon Fire Phone was used to connect to the Google Maps API and as a general sensor suite (for location services associated GPS, network discovery, etc.) for the user.

# Challenges we ran into
## Integration
The biggest problem we repeatedly encountered was integration between different parts of our design. We actually had a full IR camera we had intended to use as part of the backpack, but found that we were unable to set it up due to Harvard's WiFi blocking any unauthorized networks. With no router of our own and no way to used wired Ethernet to connect to the camera directly, we were forced to pivot to using an IR sensor to detect if anyone was behind the user. We also had large issues with passing information over Bluetooth, and it is still extremely unreliable although we are able to pair our phones with the Arduino's Bluetooth. The google maps API also proved problematic: it was very difficult to coordinate the phone's integrated location services, so most solutions required more direct address encoding.

## Demonstrating in-house
Although our product may work fairly well at a large scale, we aren't exactly able to walk all over Cambridge while demonstrating (plus, with the current frigid cold we don't think anyone would want to with us!). Therefore, we had to figure out how to best demonstrate what we were doing in a smaller environment. What we settled on was using an accelerometer in order to approximate how far we've navigated and then use some pre-programmed instructions for where to navigate to. This unfortunately limits what we can show but due to the supplies we have and the time constraints we were unable to determine a better way to demonstrate our hack.

## Android Application
The android application built for this particular project works to integrate Bluetooth connectivity, the location services framework, and the google cloud services API to provide a seamless user experience. Unfortunately, the integration step proved to be much more taxing than running each individual process in isolation, so use of the application requires a nontrivial amount of overhead from the user side.

# Accomplishments that we're proud of
As a group of bigs and littles from Olin college, we are proud of how we worked together and leveraged our varied backgrounds; our team is comprised of a junior ECE major, a sophomore ECE major, a first-year bioengineer, and a first-year mechanical engineer. Because those of us who are older have been to multiple hackathons before, we had the opportunity to be in more of a teaching role, but we still all learned from each others' unique perspectives, built something compelling to us, and survived the hackathon!

# What we learned
Through the course of the event, we all worked on project outside of our comfort zones: no one had written code for Android phones before (or figured out how to download all of the programs to make an Amazong Fire Phone act as if it were one), the two engineers who wrote a lot of the Arduino code had minimal experience with them and programming in general, and we we were constantly using new APIs, procedures, components, and tools.

# What's next for GotYourBack
GotYourBack still needs to do a lot of user testing. Through different design classes at Olin (most likely User Oriented Collaborative Design and Technology, Accessibility, and Design), we hope to learn more about accessible design and possibly iterate on our current design. If we don't iterate in-class, we will be able to continue designing our product and will reach out to communities we feel we can most help with our hack and perform extensive user testing and iteration on their feedback.
