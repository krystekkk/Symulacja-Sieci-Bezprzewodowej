#include "simulation.h"

Simulation::Simulation(WirelessNetwork* wireless_network) : wireless_network_(wireless_network)
{
}

Simulation::~Simulation()
{
}

bool Simulation::ChooseMode(int option)
{
	if (option == 1) return true;
	if (option == 2) return false;
	else return true;
}

void Simulation::StepMode()
{
	char sign;
	std::cout << "\nPlease press Enter to do a step\n";
	sign = getchar();
}

void Simulation::M2(int time)
{
	clock_ = 0;

	int mode;

	std::cout << "Available simulation modes: 1.Uninterrupted mode, 2.Step mode\n";
	std::cout << "Choose mode of simulation (type 1 or 2 and press Enter): ";
	std::cin >> mode;

	std::cout << "Simulation is running...\n";

	auto cmp = [](Event* left, Event* right) { return left->get_time() > right->get_time(); };
	Event::EventList event_list(cmp);

	auto logger = Logger();
	logger.set_level(Logger::Level::Info);

	for (int i = 0; i < wireless_network_->GetNumberOfStations(); ++i)
	{
		int temp_time = wireless_network_->GetTransmitters()->at(i)->GetExpGenerator()->RandExp(wireless_network_->lambda);

		event_list.push(new GeneratePacketEvent(temp_time, wireless_network_, &logger, &event_list, i));
	}

	while (clock_ < static_cast<int>(time))
	{
		Event* event = event_list.top();
		event_list.pop();
		clock_ = event->get_time();

		if (ChooseMode(mode) == false) StepMode();

		//std::cout << "\n";
		//logger.Info("Simulation Time: " + std::to_string(clock_));

		event->Execute();
	}

	std::cout << "\nSimulation completed!\n";
	
	std::cout << "\n\n--------------------STATYSTYKI--------------------\n\n";
	std::cout << "Liczba poprawnie odebranych pakietow: " << wireless_network_->GetChannel()->GetCorrectPackages() << "\n";
	std::cout << "Liczba retransmisji pakietow: " << wireless_network_->GetChannel()->GetRetransmittedPackages() << "\n";
	std::cout << "Liczba odrzuconych pakietow: " << wireless_network_->GetChannel()->GetLostPackages() << "\n";
	std::cout << "Srednia pakietowa stopa bledow: " << wireless_network_->GetChannel()->GetAverageBER() << "\n";
	std::cout << "Maksymalna pakietowa stopa bledow: " << wireless_network_->GetChannel()->GetMaxBER() << "\n";
	std::cout << "Srednia liczba retransmisji pakietow: " << wireless_network_->GetChannel()->GetAverageRetransmissionNumber() << "\n";
	std::cout << "Przeplywnosc systemu: " << (wireless_network_->GetChannel()->GetCorrectPackages() / (clock_ - wireless_network_->GetInitialPhase())) * 10000 << " [pakietow/s]" << "\n"; // poprawne pakiety / clock_ - czas od kiedy zbieram statystyki
	std::cout << "Srednie opoznienie pakietu: " << wireless_network_->GetChannel()->GetAverageDelayTime() / 10 << " [ms]" << "\n";
	std::cout << "Sredni czas oczekiwania: " << wireless_network_->GetChannel()->GetAverageWaitingTime() / 10 << " [ms]" << "\n";
	std::cout << "\n";

	/*
	int index = 1;
	
	std::ofstream main_seed("Main_seed-AND-lambda=" + std::to_string(wireless_network_->lambda) + "_NO." + std::to_string(index) + ".txt", std::ios_base::app | std::ios_base::out);        // Save many values to the file 
	main_seed << "Time of simulation: " << time / 10 << " [ms]\n" << "Seed: " << wireless_network_->GetMainSeed() << "\n" << "Lambda: " << wireless_network_->lambda << "\n"
		<< "Average BER: " << wireless_network_->GetChannel()->GetAverageBER() << "\n" << "Max BER: " << wireless_network_->GetChannel()->GetMaxBER() << "\n"
		<< "Przeplywnosc: " << (wireless_network_->GetChannel()->GetCorrectPackages() / (clock_ - wireless_network_->GetInitialPhase())) * 10000 << " [pakietow/s]" << "\n";
	std::ofstream przeplywnosc("Przeplywnosc-lambda=" + std::to_string(wireless_network_->lambda) + "_NO." + std::to_string(index) + ".txt", std::ios_base::app | std::ios_base::out);
	przeplywnosc << (wireless_network_->GetChannel()->GetCorrectPackages() / (clock_ - wireless_network_->GetInitialPhase())) * 10000 << "\n";
	*/
	
	/*
	std::ofstream final_statistics("Final_statistics_NO." + std::to_string(index) + ".txt", std::ios_base::app | std::ios_base::out);
	final_statistics << "Seed: " << wireless_network_->GetMainSeed() << "\n" << "Average BER: " << wireless_network_->GetChannel()->GetAverageBER() << "\n"
		<< "Max BER: " << wireless_network_->GetChannel()->GetMaxBER() << "\n"
		<< "Average retransmission number: " << wireless_network_->GetChannel()->GetAverageRetransmissionNumber() << "\n"
		<< "Bitrate: " << (wireless_network_->GetChannel()->GetCorrectPackages() / (clock_ - wireless_network_->GetInitialPhase())) * 10000 << "\n"
		<< "Average delay time [ms]: " << wireless_network_->GetChannel()->GetAverageDelayTime() / 10 << "\n"
		<< "Average waiting time [ms]: " << wireless_network_->GetChannel()->GetAverageWaitingTime() / 10 << "\n";
	*/
	
	/*
	std::ofstream p_ter_statistic("P(TER)_0.9_statistics.txt", std::ios_base::app | std::ios_base::out);
	p_ter_statistic << wireless_network_->GetChannel()->GetAverageRetransmissionNumber() << "\n";
	*/
}
