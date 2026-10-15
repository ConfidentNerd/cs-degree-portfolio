import { Component, OnInit, Input } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';
import { Trip } from '../models/trip';
import { TripDataService } from '../services/trip-data.service';
import { AuthenticationService } from '../services/authentication.service';

@Component({
  selector: 'app-trip-card',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './trip-card.component.html',
  styleUrl: './trip-card.component.css'
})
export class TripCardComponent implements OnInit {

  @Input('trip') trip: any;

  constructor(private router: Router,
              private tripDataService: TripDataService,
              private authenticationService: AuthenticationService) {}

  ngOnInit(): void {

  }

  public isLoggedIn()
  {
    return this.authenticationService.isLoggedIn();
  }

  public editTrip(trip: Trip) {
    localStorage.removeItem('tripCode');
    localStorage.setItem('tripCode', trip.code);
    this.router.navigate(['edit-trip']);
  }

  public deleteTrip(trip: Trip) {
    this.tripDataService.deleteTrip(trip.code)
    .subscribe({
      next: (value: any) => {
        console.log(value);
        window.location.reload();
      },
      error: (error: any) => {
        console.log('Error: ' + error);
      }
    })
  }
}
